/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:16:09 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/03 13:16:56 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/*
 * This functions takes a philosopher and has him
 * take both is right and left fork by locking the
 * mutexes.
 */

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	if (check_deaths(philo->data))
		return ;
	print_message(*philo, "has taken a fork.");
	sem_wait(philo->data->forks);
	if (check_deaths(philo->data))
		return ;
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
	print_message(*philo, "is eating.");
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->nbr_of_meals++;
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

void	routine(t_philo	*philo)
{
	if (philo->data->nbr_philos == 1)
	{
		sem_wait(philo->data->forks);
		print_message(*philo, "has taken a fork.");
		return ;
	}
	while (!check_deaths(philo->data))
	{
		if (check_deaths(philo->data))
			break ;
		take_forks(philo);
		if (check_deaths(philo->data))
			break ;
		ft_eat(philo);
		if (check_meals(philo->data) || check_deaths(philo->data))
			break ;
		ft_sleep(philo);
		if (check_deaths(philo->data))
			break ;
		print_message(*philo, "is thinking.");
	}
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
	long long	current_time;
	int			count;
	int			i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < data->nbr_philos)
		{
			current_time = get_time();
			if (data->must_eat != -1
				&& data->philos[i].nbr_of_meals >= data->must_eat)
				count++;
			if ((current_time - data->philos[i].last_meal_time)
				> data->time_to_die)
				return (&data->philos[i]);
			i++;
		}
		if (count == data->nbr_philos)
			return (NULL);
	}
}