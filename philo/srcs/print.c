/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:36:01 by martina           #+#    #+#             */
/*   Updated: 2023/09/14 15:03:44 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (!philo->data->dead || ft_strcmp(DIED, str) == 0)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		if (ft_strcmp(DIED, str) == 0)
		{
			philo->data->dead = 1;
		}
		else
		{
			philo->data->dead = 0;
		}
	}
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	philo->time_to_die = get_time() - philo->starting_time;
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
	philo->time_to_die = get_time() - philo->starting_time;
	messages(EATING, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->time_to_die = 0;
	philo->starting_time = get_time();
	messages(SLEEPING, philo);
}

void	eat(t_philo *philo)
{
	philo->eating_time = 0;
	philo->starting_eat = get_time();
	while (philo->eating_time < philo->data->eat_time)
	{
		philo->time_to_die = get_time() - philo->starting_time;
		philo->eating_time = get_time() - philo->starting_eat;
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
