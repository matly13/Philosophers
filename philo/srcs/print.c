/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:36:01 by martina           #+#    #+#             */
/*   Updated: 2023/09/13 17:47:58 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// int	thread_init(t_data *data)
// {
//     int	i;

//     i = -1;
//     data->start_time = get_time();
//     while (++i < data->philo_num)
//     {
//         if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
//             return (error(TH_ERR, data));
//         pthread_detach(data->tid[i]);
//     }
//     while (data->dead == 0 && data->finished == 0)
//         ft_usleep(0);
//     ft_exit(data);
//     return (0);
// }

// int	input_checker(char **argv)
// {
// 	int	i;
// 	int	j;

// 	i = 1;
// 	while (argv[i])
// 	{
// 		j = 0;
// 		while (argv[i][j])
// 		{
// 			if (argv[i][j] == ' ')
// 			{
// 				j++;
// 				continue ;
// 			}
// 			if ((argv[i][j] < 48 || argv[i][j] > 57))
// 				return (error(ERR_IN_1, NULL));
// 			j++;
// 		}
// 		i++;
// 	}
//     return (0);
// }

void    messages(char *str, t_philo *philo)
{
	u_int64_t time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead || ft_strcmp(DIED, str) == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = (ft_strcmp(DIED, str) == 0) ? 1 : 0;
	}
	pthread_mutex_unlock(&philo->data->write);
}

void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	philo->time_to_die = get_time() - philo->starting_time;
	// ft_check_death(philo);
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
	philo->time_to_die = get_time() - philo->starting_time;
	// ft_check_death(philo);
	messages(EATING, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->time_to_die = 0;
	philo->starting_time = get_time();
	messages(SLEEPING, philo);
	// while (philo->sleeping_time < philo->data->sleep_time)
	// 	philo->time_to_die = get_time() - philo->data->start_time;
	// ft_usleep(philo->data->sleep_time);
}

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->lock);
	philo->eating_time = 0;
	philo->starting_eat = get_time();
	while (philo->eating_time < philo->data->eat_time)
	{
		// write(1,"ciao5\n", 6);
		philo->time_to_die = get_time() - philo->starting_time;
		philo->eating_time = get_time() - philo->starting_eat;
		// printf("id: %d eating_time: %llu\n", philo->id, philo->eating_time);
	}
	drop_forks(philo);
	philo->eat_cont++;
}


void	sleeping(t_philo *philo)
{
	philo->sleeping_time = 0;
	philo->starting_sleep = get_time();
	while (philo->sleeping_time < philo->data->sleep_time)
	{
		philo->time_to_die = get_time() - philo->starting_time;
		philo->sleeping_time = get_time() - philo->starting_sleep;
	}
	messages(THINKING, philo);
}