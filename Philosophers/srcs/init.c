/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:25:11 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/15 12:40:44 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_inputs(char **argv)
{
	
}

int	init(int argc, char **argv, t_data *data)
{
	if ((argc != 4 && argc != 5) || check_inputs(argv))
		return (1);
	data->nbr_philosophers = ft_atoi(argv[1]);
}