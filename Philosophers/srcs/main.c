/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/14 11:18:29 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	ft_printf("Error\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	if (argc > 5 || argc < 4)
		ft_error();
	
}
