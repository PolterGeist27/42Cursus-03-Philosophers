/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:23:14 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/15 15:12:52 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	The ft_atoi() function receives a char array, 
	parses through all spaces and tabs in the beginning,
	checks if there is a signal ("+" or "-"), 
	and then converts the number on the String to an integer and returns it.
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
