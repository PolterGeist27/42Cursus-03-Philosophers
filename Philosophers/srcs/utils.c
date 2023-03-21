/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:23:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 18:14:13 by diogmart         ###   ########.fr       */
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

	time = get_time();
	printf("%lld %d %s\n", time, philo.ID, msg);
}
