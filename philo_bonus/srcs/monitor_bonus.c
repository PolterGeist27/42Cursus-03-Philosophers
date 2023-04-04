/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:12:35 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 12:30:59 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	create_monitor_threads(t_data *data)
{
	pthread_t	monitor;
	pthread_t	end;

	pthread_create(&monitor, 0, monitoring, data);
	pthread_create(&end, 0, finish_all, data);
	pthread_join(monitor, 0);
	pthread_join(end, 0);
	return (0);
}

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	sem_wait(data->finish);
	while (i < data->nbr_philos)
	{
		sem_post(data->meals);
		i++;
	}
	return (0);
}

void	*finish_all(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		sem_wait(data->meals);
		data->all_ate--;
		if (data->all_ate == 0)
		{
			sem_post(data->finish);
			while (i < data->nbr_philos)
			{
				kill(data->philos[i].pid, SIGKILL);
				i++;
			}
			return (0);
		}
	}
	return (0);
}
