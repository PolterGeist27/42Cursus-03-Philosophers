/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:16:09 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 12:28:59 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * This functions takes a philosopher and has him
 * take both is right and left fork by locking the
 * mutexes.
 */

void	take_forks(t_data *data)
{
	sem_wait(data->forks);
	print_message(data, data->index, "has taken a fork.");
	sem_wait(data->forks);
	print_message(data, data->index, "has taken a fork.");
}

/*
 * This function represents the philosopher eating
 * which takes time_to_eat milliseconds to complete
 * and then unlocks both mutexes, as if the philosopher
 * is putting the forks down on the table again.
 */

void	ft_eat(t_data *data)
{
	print_message(data, data->index, "is eating.");
	sem_wait(data->philos[data->index].can_die);
	data->philos[data->index].last_meal_time = get_time();
	sem_post(data->philos[data->index].can_die);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->philos[data->index].nbr_of_meals++;
	if (data->philos[data->index].nbr_of_meals == data->must_eat
		&& data->must_eat != -1)
		sem_post(data->meals);
}

/*
 * ft_sleep() represents the philosophers sleeping,
 * which lasts for time_to_sleep milliseconds.
 */

void	ft_sleep(t_data *data)
{
	print_message(data, data->index, "is sleeping.");
	usleep(data->time_to_sleep * 1000);
}

/*
 * This function is the routine for the philosophers,
 * they start by eating, when they finish they sleep
 * and after they wake up they start thinking until
 * they can eat again;
 */

void	routine(t_data	*data)
{
	pthread_t	th_reaper;

	if (data->index % 2)
		usleep(1000);
	pthread_create(&th_reaper, NULL, reaper, data);
	if (data->nbr_philos == 1)
	{
		sem_wait(data->forks);
		print_message(data, data->index, "has taken a fork.");
		return ;
	}
	while (1)
	{
		take_forks(data);
		ft_eat(data);
		ft_sleep(data);
		print_message(data, data->index, "is thinking.");
	}
}

/*
 * The point of this function is to run on a separate
 * thread to monitor all the philosophers.
 */

void	*reaper(void *arg)
{
	t_data		*data;
	long long	current_time;

	data = (t_data *)arg;
	while (1)
	{
		current_time = get_time();
		if ((current_time - data->philos[data->index].last_meal_time) > data->time_to_die)
		{
			sem_wait(data->philos[data->index].can_die);
			print_message(data, data->index, "has died.");
			sem_post(data->finish);
			sem_post(data->philos[data->index].can_die);
			exit(0);
		}
	}
	return (0);
}
