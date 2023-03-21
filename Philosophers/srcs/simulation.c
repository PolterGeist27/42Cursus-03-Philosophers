/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:48:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 11:46:04 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_simulation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(data->philos[i].thread, NULL, &routine, &data->philos[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_detach(*data->philos[i].thread);
		usleep(1000);
		i++;
	}
	return  (0);
}
