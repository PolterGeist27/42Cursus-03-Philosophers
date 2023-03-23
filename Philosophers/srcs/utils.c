/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:23:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/22 14:32:23 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
 * The ft_atoi() function receives a char array,
 * parses through all spaces and tabs in the beginning,
 * checks if the number is negative, then converts the number
 * to an integer and returns it.
*/

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			h;
	long int	final;

	i = 0;
	j = 0;
	final = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			j++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		h = str[i] - 48;
		final = (final * 10) + h;
		i++;
	}
	if (j % 2 == 1)
		final *= -1;
	return (final);
}

/*
 * This function get the current time and returns it
 * in milliseconds.
 *
 * Note: gettimeofday() returns a struct timeval with
 * the total time being timeval.tv_sec + timeval.tv_usec,
 * NOT the same time in two different measurements
 */

long long	get_time(void)
{
	struct timeval tv;
	long long time_ms;

	gettimeofday(&tv, NULL);
	time_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return  (time_ms);
}

/*
 * This function receives a philosopher and a message to print
 * and prints the message in the format "<time in ms> <philo ID> <message>"
 *
 * An example of a message is "215 5 has taken a fork."
 */

void	print_message(t_philo philo, char *msg)
{
	long long	time;

	pthread_mutex_lock(&philo.data->print);
	time = get_time() - philo.data->init_time;
	printf("%lld %d %s\n", time, philo.ID, msg);
	pthread_mutex_unlock(&philo.data->print);
}

/*
 * This function checks if every philo has reached the
 * minimum meal goal set by the user.
 */

int	check_meals(t_data *data)
{
	int nbr_of_meals;
	int	i;

	i = 0;
	nbr_of_meals = data->must_eat;
	while (i < data->nbr_philos)
	{
		if (data->philos[i].nbr_of_meals < nbr_of_meals)
			return (0);
		i++;
	}
	return (1);
}

int check_deaths(t_data *data)
{
	long long	current_time;
	int i;

	i = 0;
	current_time = get_time();
	while (i < data->nbr_philos)
	{
		if ((current_time - data->philos[i].last_meal_time) > data->time_to_die)
			return (1);
		i++;
	}
	return (0);
}
