/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:16:09 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 18:18:17 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * This functions takes a philosopher and has him
 * take both is right and left fork by locking the
 * mutexes.
 */

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message(*philo, "has taken a fork.");
	pthread_mutex_lock(philo->left_fork);
	print_message(*philo, "has taken a fork.");
}

/*
 * This function represents the philosopher eating
 * which takes time_to_eat milliseconds to complete
 * and then unlocks both mutexes, as if the philosopher
 * is putting the forks down on the table again.
 */

void ft_eat(t_philo *philo)
{
	print_message(*philo, "is eating.");
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000); // time is in ms
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->nbr_of_meals++;
}

/*
 * ft_sleep() represents the philosophers sleeping,
 * which lasts for time_to_sleep milliseconds.
 */

void ft_sleep(t_philo *philo)
{
	print_message(*philo, "is sleeping.");
	usleep(philo->data->time_to_sleep * 1000); // time is in ms
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		print_message(*philo, "is thinking.");
		if (philo->nbr_of_meals > 3)
			break;
	}
	return ((void *)philo);
}
