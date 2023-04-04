/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 12:19:18 by diogmart         ###   ########.fr       */
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
	data->index = 0;
	data->init_time = get_time();
	while (data->index < data->nbr_philos)
	{
		data->philos[data->index].last_meal_time = get_time();
		data->philos[data->index].pid = fork();
		if (data->philos[data->index].pid == 0)
		{
			routine(data);
			break ;
		}
		data->index++;
	}
	create_monitor_threads(data);
	return (0);
}
