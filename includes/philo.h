/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martina <martina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:38 by martina           #+#    #+#             */
/*   Updated: 2023/09/05 15:40:58 by martina          ###   ########.fr       */
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


struct	s_data; //this line is to define the structure before actually saying what's inside it

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t       t1;
	int             id;
	int             eat_cont;
	int             status;
	int             eating;
	uint64_t        time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
} t_philo;

typedef struct s_data
{
	pthread_t       *tid;
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	t_philo         *philos;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
} t_data;

// ACTIONS
//void	eating(t_philo *philo);
//void	sleeping(t_philo *philo);
//void	thinking(t_philo *philo);
int		leftfork(t_philo *philo);
int		rightfork(t_philo *philo);
void	*routine(void *arg);

// UTILS
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
int		ft_usleep(useconds_t time);
int		ft_strcmp(char *s1, char *s2);
//int		error(char *str);
uint64_t	get_time(void);
//int		ft_isdigit(char **argv);
//int   	error(char *str, t_data *data);


// INIT
int		alloc(t_data *data);
int		init(t_data *data, char **argv, int argc);
int		init_data(t_data *data, char **argv, int argc);
int		init_forks(t_data *data);
void	init_philos(t_data *data);
int		thread_init(t_data *data);
int		input_checker(char **argv);

//int		init_philo(t_philo **philo, int argc, char **argv);
//int		start_philo(t_philo *philo);
//int		join_philo(t_philo *philo);
//int		destroy_philo(t_philo *philo);

// PRINT
void	messages(char *str, t_philo *philo);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);

#endif
