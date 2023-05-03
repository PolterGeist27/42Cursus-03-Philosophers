/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:16:09 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/03 12:38:25 by diogmart         ###   ########.fr       */
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
	if (philo->id % 2)
	{
		take_forks_reverse(philo);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	if (!check_finish(philo->data))
		print_message(*philo, "has taken a fork.");
	pthread_mutex_lock(philo->right_fork);
	if (!check_finish(philo->data))
		print_message(*philo, "has taken a fork.");
}

/*
 * This function represents the philosopher eating
 * which takes time_to_eat milliseconds to complete
 * and then unlocks both mutexes, as if the philosopher
 * is putting the forks down on the table again.
 */

void	ft_eat(t_philo *philo)
{
	if (!check_finish(philo->data))
	{
		pthread_mutex_lock(&philo->can_die);
		print_message(*philo, "is eating.");
		philo->last_meal_time = get_time();
		philo->nbr_of_meals++;
		pthread_mutex_unlock(&philo->can_die);
	}
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

/*
 * ft_sleep() represents the philosophers sleeping,
 * which lasts for time_to_sleep milliseconds.
 */

void	ft_sleep(t_philo *philo)
{
	print_message(*philo, "is sleeping.");
	usleep(philo->data->time_to_sleep * 1000);
}

/*
 * This function is the routine for the philosophers,
 * they start by eating, when they finish they sleep
 * and after they wake up they start thinking until
 * they can eat again;
 */

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nbr_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(*philo, "has taken a fork.");
		pthread_mutex_unlock(philo->left_fork);
		return ((void *)philo);
	}
	while (!check_finish(philo->data))
	{
		if (check_finish(philo->data))
			break ;
		take_forks(philo);
		ft_eat(philo);
		if (check_finish(philo->data))
			break ;
		ft_sleep(philo);
		if (check_finish(philo->data))
			break ;
		print_message(*philo, "is thinking.");
	}
	return ((void *)philo);
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
	t_philo		*result;
	int			count;

	data = (t_data *)arg;
	while (1)
	{
		count = 0;
		result = reaper_loop(data, &count);
		if (result != NULL)
			return (result);
		if (count == data->nbr_philos)
		{
			pthread_mutex_lock(&data->check_finish);
			data->can_finish = 1;
			pthread_mutex_unlock(&data->check_finish);
			return (NULL);
		}
	}
}
