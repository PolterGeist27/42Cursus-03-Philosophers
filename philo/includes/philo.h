/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:11:59 by diogmart          #+#    #+#             */
/*   Updated: 2023/05/03 11:02:01 by diogmart         ###   ########.fr       */
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
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		init_time;
	int				can_finish;
	struct s_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	check_finish;
}	t_data;

typedef struct s_philo {
	int				id;
	int				nbr_of_meals;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	can_die;
	t_data			*data;
}	t_philo;

//	main.c
void			free_data(t_data *data);
long			ft_atol(const char *str);

//	utils.c
int				ft_atoi(const char *str);
long long		get_time(void);
void			print_message(t_philo philo, char *msg);
int				check_meals(t_data *data);
int				check_deaths(t_data *data);
void			*reaper(void *arg);

//	actions.c
void			take_forks(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);
void			*routine(void *arg);

//	init.c
int				init(int argc, char **argv, t_data *data);
int				check_inputs(char **argv, int argc);
pthread_mutex_t	*init_forks(int nbr_philosophers);
t_philo			*init_philos(t_data **data);

//	simulation.c
int				init_simulation(t_data *data);
void			end_simulation(pthread_t th_reaper, t_data *data);

//	utils2.c
t_philo			*reaper_loop(t_data *data, int *count);
void			take_forks_reverse(t_philo *philo);
int				check_finish(t_data *data);

#endif
