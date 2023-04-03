/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/03 13:56:14 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * THe init_simulation() function starts the print semaphore (so that
 * only 1 process can write at a time) and then starts all the
 * processes for the philosophers. After that it creates a thread for
 * the reaper and calls the end_simulation() function.
 */

int	init_simulation(t_data *data)
{
	pthread_t	th_reaper;
	int			i;

	i = 0;
	data->init_time = get_time();
	while (i < data->nbr_philos)
	{
		data->philos[i].last_meal_time = get_time();
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			routine(&data->philos[i]);
			break;
		}
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
 * a philo died.
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
		//kill(data->philos[i].pid, SIGTERM);
		i++;
	}
	sem_close(data->print);
}
