/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:10:12 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/03 12:37:17 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*reaper_loop(t_data *data, int *count)
{
	long long	current_time;
	int			i;
	int			nbr_meals;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_lock(&data->philos[i].can_die);
		nbr_meals = data->philos[i].nbr_of_meals;
		if (data->must_eat != -1
			&& nbr_meals >= data->must_eat)
			(*count)++;
		current_time = get_time();
		if (current_time - data->philos[i].last_meal_time > data->time_to_die)
		{
			pthread_mutex_lock(&data->check_finish);
			data->can_finish = 1;
			pthread_mutex_unlock(&data->check_finish);
			pthread_mutex_unlock(&data->philos[i].can_die);
			return (&data->philos[i]);
		}
		pthread_mutex_unlock(&data->philos[i].can_die);
		i++;
	}
	return (NULL);
}

void	take_forks_reverse(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (!check_finish(philo->data))
		print_message(*philo, "has taken a fork.");
	pthread_mutex_lock(philo->left_fork);
	if (!check_finish(philo->data))
		print_message(*philo, "has taken a fork.");
}

int	check_finish(t_data *data)
{
	pthread_mutex_lock(&data->check_finish);
	if (data->can_finish == 1)
	{
		pthread_mutex_unlock(&data->check_finish);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->check_finish);
		return (0);
	}
}
