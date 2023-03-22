/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/22 16:33:11 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * THe init_simulation() function starts the print mutex (so that
 * only 1 thread can write at a time) and then starts all the
 * threads for the philosophers. After that it creates a thread for
 * the reaper and calls the end_simulation() function.
 */

int	init_simulation(t_data *data)
{
	pthread_t	th_reaper;
	int i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->nbr_philos)
	{
		data->init_time = get_time();
		data->philos[i].last_meal_time = get_time();
		pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]);
		usleep(1000);
		i++;
	}
	pthread_create(&th_reaper, NULL, &reaper, data);
	end_simulation(th_reaper, data);
	return (0);
}

/*
 * The end_simulation() function waits for the reaper thread
 * to finish (by using pthread_join() instead of detach), then
 * depending on the result returned by the thread prints whether
 * the simulation was successful or if a philo died.
 * Afterwards it destroys all the mutexes and detaches
 * all threads.
 */

void	end_simulation(pthread_t th_reaper, t_data *data)
{
	void *result;
	int i;

	pthread_join(th_reaper, &result);
	if (!result)
		printf("The simulation was successful!\n");
	else
		print_message(*(t_philo *)(result), "has died.");
	i = 0;
	pthread_mutex_destroy(&data->print);
	while (i < data->nbr_philos)
	{
		pthread_detach(data->philos[i].thread);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
