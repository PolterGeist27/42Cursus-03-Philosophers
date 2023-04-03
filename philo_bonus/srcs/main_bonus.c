/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/03 14:58:36 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_data(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_unlink("forks");
	sem_unlink("print");
	free(data->philos);
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

long		ft_atol(const char *str)
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
