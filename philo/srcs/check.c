/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbasile <mbasile@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:52:47 by mbasile           #+#    #+#             */
/*   Updated: 2023/09/14 14:50:20 by mbasile          ###   ########.fr       */
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

int	checker(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->philo_num)
		{
			if (!ft_check_death(&data->philos[i])
				|| data->finished == data->philo_num)
			{
				ft_exit(data);
				return (0);
			}
		}
	}
	return (1);
}

int	input_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (error(ERR_IN_1, NULL));
			j++;
		}
		i++;
	}
	return (0);
}

int	alloc(t_data *data)
{
	data->tid = malloc(sizeof(pthread_t) * data->philo_num);
	if (!data->tid)
		return (error(ALLOC_ERR_1, data));
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
		return (error(ALLOC_ERR_2, data));
	data->philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!data->philos)
		return (error(ALLOC_ERR_3, data));
	return (0);
}
