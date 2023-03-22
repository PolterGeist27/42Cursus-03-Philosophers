/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/22 14:51:39 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	while (i < data->nbr_philos)
	{
		pthread_detach(data->philos[i].thread);
		i++;
	}
}
