/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:39:38 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/04 12:49:36 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	free_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->meals);
	sem_close(data->finish);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("meals");
	sem_unlink("finish");
}

void	free_data(t_data *data)
{
	char	*id;
	int		i;

	i = 0;
	free_semaphores(data);
	while (i < data->nbr_philos)
	{
		id = ft_itoa(data->philos[i].id);
		sem_close(data->philos[i].can_die);
		sem_unlink(id);
		free(id);
		i++;
	}
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
