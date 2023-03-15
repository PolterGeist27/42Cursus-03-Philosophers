/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/15 15:08:17 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data || init(argc, argv, data))
	{
		printf("Error\n");
		free(data);
		return (1);
	}
}
