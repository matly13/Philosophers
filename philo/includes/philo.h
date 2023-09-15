/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:38 by martina           #+#    #+#             */
/*   Updated: 2023/09/14 14:23:01 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "pthread.h"
# include "sys/time.h"

# define ALLOC_ERR_1 "ERROR WHILE ALLOCATING THREADS IDs"
# define ALLOC_ERR_3 "ERROR WHILE ALLOCATING PHILOS"
# define ALLOC_ERR_2 "ERROR WHILE ALLOCATING FORKS"
//	input_err
# define ERR_IN_1 "INVALID INPUT CHARACTER"
# define ERR_IN_2 "INVALID INPUT VALUES"
//	pthread_err
# define TH_ERR "ERROR WHILE CREATING THREADS"
# define JOIN_ERR "ERROR WHILE JOINING THREADS"
# define INIT_ERR_1 "ERROR WHILE INIT FORKS"
//	time_err
# define TIME_ERR "UNABLE TO RETRIVE UTC"
//	philo_msg
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"
# define FULL "is full"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	uint64_t		starting_time;
	uint64_t		starting_eat;
	uint64_t		starting_sleep;
	uint64_t		eating_time;
	uint64_t		sleeping_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				started;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

// ACTIONS
int			leftfork(t_philo *philo);
int			rightfork(t_philo *philo);
void		*routine(void *arg);

// CHECK
int			checker(t_data *data);
int			ft_check_death(t_philo	*philo);
int			input_checker(char **argv);
int			alloc(t_data *data);

// UTILS
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_usleep(useconds_t time);
int			ft_strcmp(char *s1, char *s2);
u_int64_t	get_time(void);

// INIT
int			init(t_data *data, char **argv, int argc);
int			init_data(t_data *data, char **argv, int argc);
int			init_forks(t_data *data);
void		init_philos(t_data *data);
int			thread_init(t_data *data);
int			error(char *str, t_data *data);
void		ft_exit(t_data *data);

// PRINT
void		messages(char *str, t_philo *philo);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
void		sleeping(t_philo *philo);
void		eat(t_philo *philo);;
#endif
