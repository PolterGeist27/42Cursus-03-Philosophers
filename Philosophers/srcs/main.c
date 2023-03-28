/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/28 14:40:29 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_data(t_data *data)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
	if (data != NULL)
		free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data || init(argc, argv, data))
	{
		write(2, "Error\n", 6);
		free(data);
		return (1);
	}
	init_simulation(data);
	free_data(data);
}
