/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martina <martina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:36:01 by martina           #+#    #+#             */
/*   Updated: 2023/09/05 14:40:25 by martina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void messages(char *str, t_philo *philo)
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
    pthread_mutex_lock(philo->l_fork);
    messages(TAKE_FORKS, philo);
}

void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    messages(SLEEPING, philo);
    ft_usleep(philo->data->sleep_time);
}

void eat(t_philo *philo)
{
    take_forks(philo);

    pthread_mutex_lock(&philo->lock);
    philo->eating = 1;
    philo->time_to_die = get_time() + philo->data->death_time;
    messages(EATING, philo);
    philo->eat_cont++;
    ft_usleep(philo->data->eat_time);
    philo->eating = 0;
    pthread_mutex_unlock(&philo->lock);

    drop_forks(philo);
}

