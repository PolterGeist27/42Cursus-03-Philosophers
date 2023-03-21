/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:25:11 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 11:38:14 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * Checks if all the values from the input are valid
 * (for example we can't have a negative number of philosophers)
*/

int	check_inputs(t_data *data, int argc)
{
	if (data->nbr_philos <= 0)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->must_eat <= 0)
		return (1);
	return (0);
}

/*
 * Creates an array of t_philo structs, one for each
 * philo in the simulation, and initializes all of
 * their values, except the threads.
 */

t_philo	*init_philos(t_data **data)
{
	t_philo *philos;
	int i;

	i = 0;
	philos = malloc(sizeof(t_philo) * (*data)->nbr_philos);
	if (!philos)
		return  (NULL);
	while (i <= (*data)->nbr_philos)
	{
		philos[i].ID = i + 1;
		philos[i].nbr_of_meals = 0;
		philos[i].last_meal_time = 0; // ????
		philos[i].left_fork = &(*data)->forks[(i + 1) % (*data)->nbr_philos];
		philos[i].right_fork = &(*data)->forks[i];
		philos[i].data = *data;
		i++;
	}
	return (philos);
}

/*
 * Creates an array of mutex variables, each representing a fork,
 * that is identified by its index.
*/

pthread_mutex_t *init_forks(int nbr_philosophers)
{
	pthread_mutex_t *forks;
	int i;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr_philosophers);
	if (!forks)
		return (NULL);
	while (i < nbr_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

/*
 * Initializes all the variables in "data" to the given values
 * and sends them to check_inputs() for validation.
*/

int	init(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->forks = init_forks(data->nbr_philos);
	data->philos = init_philos(&data);
	if (!data->forks || !data->philos)
		return (1);
	return (check_inputs(data, argc));
}
