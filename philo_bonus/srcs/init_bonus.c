/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:25:11 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 12:52:29 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * Checks if all the values from the input are valid
 * (for example we can't have a negative number of philosophers)
*/

int	check_inputs(char **argv, int argc)
{
	long	int_max;

	int_max = 2147483647;
	if ((ft_atol(argv[1]) <= 0)
		|| (int_max < ft_atol(argv[1])))
		return (1);
	if ((ft_atol(argv[2]) <= 0)
		|| (int_max < ft_atol(argv[2])))
		return (1);
	if ((ft_atol(argv[3]) <= 0)
		|| (int_max < ft_atol(argv[3])))
		return (1);
	if ((ft_atol(argv[4]) <= 0)
		|| (int_max < ft_atol(argv[4])))
		return (1);
	if (argc == 6 && ((ft_atol(argv[5]) <= 0)
			|| (int_max < ft_atol(argv[5]))))
		return (1);
	return (0);
}

/*
 * Creates an array of t_philo structs, one for each
 * philo in the simulation, and initializes all of
 * their values, except the process IDs.
 */

t_philo	*init_philos(t_data **data)
{
	t_philo	*philos;
	char	*id;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * (*data)->nbr_philos);
	if (!philos)
		return (NULL);
	while (i < (*data)->nbr_philos)
	{
		philos[i].id = i + 1;
		philos[i].nbr_of_meals = 0;
		philos[i].last_meal_time = get_time();
		id = ft_itoa(philos[i].id);
		sem_unlink(id);
		philos[i].can_die = sem_open(id, O_CREAT, 0644, 1);
		free(id);
		i++;
	}
	return (philos);
}

int	init_semaphores(t_data **data)
{
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("print");
	sem_unlink("finish");
	(*data)->forks = sem_open("forks", O_CREAT, 0644, (*data)->nbr_philos);
	(*data)->meals = sem_open("meals", O_CREAT, 0644, 0);
	(*data)->print = sem_open("print", O_CREAT, 0644, 1);
	(*data)->finish = sem_open("finish", O_CREAT, 0644, 0);
	if ((*data)->forks == SEM_FAILED || (*data)->meals == SEM_FAILED
		|| (*data)->print == SEM_FAILED || (*data)->finish == SEM_FAILED)
		return (1);
	return (0);
}

/*
 * Initializes all the variables in "data" to the given values
 * and sends them to check_inputs() for validation.
*/

int	init(int argc, char **argv, t_data *data)
{
	if ((argc != 5 && argc != 6) || check_inputs(argv, argc))
		return (1);
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->all_ate = data->nbr_philos;
	data->philos = init_philos(&data);
	if (init_semaphores(&data))
	{
		free_semaphores(data);
		return (1);
	}
	if (!data->philos)
	{
		free(data->philos);
		return (1);
	}
	return (0);
}
