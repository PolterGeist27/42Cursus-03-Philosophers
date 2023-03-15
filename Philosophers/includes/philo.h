/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:11:59 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/15 12:39:20 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data {
	int	nbr_philosophers;
	int nbr_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_of_times_each_philosopher_must_eat;
} t_data;

//	main.c

//	utils.c
int	ft_atoi(const char *str);

//	init.c
int	init(int argc, char **argv, t_data *data);
int check_inputs(char **argv);

#endif