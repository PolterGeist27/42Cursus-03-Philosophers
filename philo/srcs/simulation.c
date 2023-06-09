/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/03 10:18:52 by diogmart         ###   ########.fr       */
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
	int			i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	data->init_time = get_time();
	while (i < data->nbr_philos)
	{
		data->philos[i].last_meal_time = get_time();
		pthread_create(&data->philos[i].thread,
			NULL, &routine, &data->philos[i]);
		if (i % 2 == 0)
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
 * a philo died or not, and prints if so. Afterwards it destroys 
 * all the mutexes and joins all threads.
 *
 * Note: We need to use pthread_join() to avoid leaks.
 */

void	end_simulation(pthread_t th_reaper, t_data *data)
{
	void	*result;
	int		i;

	pthread_join(th_reaper, &result);
	if (result)
		print_message(*(t_philo *)(result), "has died.");
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i++ < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philos[i].can_die);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->print);
}
