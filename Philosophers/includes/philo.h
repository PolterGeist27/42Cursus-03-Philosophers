/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:11:59 by diogmart          #+#    #+#             */
/*   Updated: 2023/03/21 11:47:07 by diogmart         ###   ########.fr       */
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
	int	nbr_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
	long long	init_time;
	struct s_philo *philos;
	pthread_mutex_t *forks;
} t_data;

typedef struct s_philo {
	int	ID;
	int	nbr_of_meals;
	long long	last_meal_time;
	pthread_t	*thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data	*data;
} t_philo;

//	main.c

//	utils.c
int	ft_atoi(const char *str);
long long	get_time(void);
void	print_message(t_philo philo, char *msg);

//	actions.c
void	take_forks(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	*routine(void *arg);

//	init.c
int	init(int argc, char **argv, t_data *data);
int check_inputs(t_data *data, int argc);
pthread_mutex_t	*init_forks(int nbr_philosophers);
t_philo	*init_philos(t_data **data);
int	init_simulation(t_data *data);

#endif