/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 11:54:03 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_data(t_data *data)
{
	free(data->forks);
	free(data->philos);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data || init(argc, argv, data))
	{
		printf("Error\n");
		free_data(data);
		return (1);
	}
	init_simulation(data);
	free_data(data);
}
