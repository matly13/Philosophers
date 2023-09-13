/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:14:34 by martina           #+#    #+#             */
/*   Updated: 2023/09/13 18:36:20 by mbasile          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_death(t_philo	*philo)
{
	if (philo->time_to_die >= philo->data->death_time)
	{
		messages(DIED, philo);
		return (0);
	}
	return (1);
}

void    *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->data->started < philo->data->philo_num)
		usleep(10);
	philo->starting_time = get_time();
	while (1)
	{
		if (philo->data->philo_num == 1)
		{
			messages(TAKE_FORKS, philo);
			ft_usleep(philo->data->death_time);
			messages(DIED, philo);
			philo->data->dead = 1;
			break ;
		}
		take_forks(philo);
		eat(philo);
		if (philo->data->meals_nb != -1 && philo->eat_cont == philo->data->meals_nb)
		{
			messages(FULL, philo);
			philo->data->finished++;
			break ;
		}
		sleeping(philo);
	}
	return (NULL);
}

int leftfork(t_philo *philo)
{
	if (philo->id == 1)
		return (philo->data->philo_num - 1);
	else
		return (philo->id - 2);
}

int rightfork(t_philo *philo)
{
	if (philo->id == philo->data->philo_num)
		return (0);
	else
		return (philo->id - 1);
}
