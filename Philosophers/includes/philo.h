/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:11:59 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/20 13:08:44 by diogmart         ###   ########.fr       */
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
	pthread_mutex_t *forks;
	pthread_t *philosophers;
} t_data;

//	main.c

//	utils.c
int	ft_atoi(const char *str);
long long	get_time(void);

//	init.c
int	init(int argc, char **argv, t_data *data);
int check_inputs(t_data *data, int argc);
pthread_mutex_t	*init_forks(int nbr_philosophers);

#endif