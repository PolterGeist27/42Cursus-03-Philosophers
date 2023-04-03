/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:16:09 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/03 15:02:34 by diogmart         ###   ########.fr       */
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
	data->philos[data->index].last_meal_time = get_time();
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->philos[data->index].nbr_of_meals++;
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
 * It checks if any philosopher has died or if they all
 * achieved the number of meals required to end the simulation.
 */

void	*reaper(void *arg)
{
	t_data		*data;
	long long	current_time;
	int			count;
	int			i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->nbr_philos)
		{
			current_time = get_time();
			if (data->must_eat != -1
				&& data->philos[i].nbr_of_meals >= data->must_eat)
				count++;
			if ((current_time - data->philos[i].last_meal_time)
				> data->time_to_die)
			{
				print_message(data, i, "has died.");
				return ((void *)1);
			}
			i++;
		}
		if (count == data->nbr_philos)
			return (NULL);
	}
}
