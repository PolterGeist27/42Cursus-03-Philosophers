/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:11:59 by diogmart          #+#    #+#             */
/*   Updated: 2023/04/03 14:44:08 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_data {
	int 			index;
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		init_time;
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*print;
}	t_data;

typedef struct s_philo {
	int				id;
	int				nbr_of_meals;
	long long		last_meal_time;
	int				pid;
	t_data			*data;
}	t_philo;

//	main.c
void			free_data(t_data *data);

//	utils.c
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
long long		get_time(void);
void			print_message(t_data *data, int index, char *msg);
int				check_meals(t_data *data);
int				check_deaths(t_data *data);
void			*reaper(void *arg);

//	actions.c
void			take_forks(t_data *data);
void			ft_eat(t_data *data);
void			ft_sleep(t_data *data);
void			routine(t_data *data);

//	init.c
int				init(int argc, char **argv, t_data *data);
int				check_inputs(char **argv, int argc);
//pthread_mutex_t	*init_forks(int nbr_philosophers);
t_philo			*init_philos(t_data **data);

//	simulation.c
int				init_simulation(t_data *data);
void			end_simulation(pthread_t th_reaper, t_data *data);

#endif
