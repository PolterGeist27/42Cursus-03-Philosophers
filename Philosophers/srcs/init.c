/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:25:11 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/15 15:03:10 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
	Checks if all the values from the input are valid
	(for example we can't have a negative number of philosophers)
*/

int	check_inputs(t_data *data, int argc)
{
	if (data->nbr_philosophers <= 0)
		return (1);
	if (data->time_to_die <= 0)
		return (1);
	if (data->time_to_eat <= 0)
		return (1);
	if (data->time_to_sleep <= 0)
		return (1);
	if (argc == 6 && data->nbr_of_times_each_philosopher_must_eat <= 0)
		return (1);
	return (0);
}

/*
	Initializes all the variables in "data" to the given values
	and sends them to check_inputs() for validation
*/

int	init(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (1);
	data->nbr_philosophers = ft_atoi(argv[1]);
	data->nbr_forks = data->nbr_philosophers;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->nbr_of_times_each_philosopher_must_eat = 0;
	return (check_inputs(data, argc));
}
