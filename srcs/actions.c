/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martina <martina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:14:34 by martina           #+#    #+#             */
/*   Updated: 2023/09/05 15:21:58 by martina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->data->dead == 0)
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
            break ;
        }
        {
            messages(DIED, philo);
            philo->data->dead = 1;
            break ;
        }
        drop_forks(philo);
        messages(THINKING, philo);
    }
    return (NULL);
}


//void	eating(t_philo *philo)
//{
//    pthread_mutex_lock(philo->forks);
//    print_status(philo, FORK);
//    pthread_mutex_lock(philo->forks);
//    print_status(philo, FORK);
//   print_status(philo, EATING);
//    philo->eat_time = get_time();
//    ft_usleep(philo->eat_time);
//    philo->eat_cont++;
//    pthread_mutex_unlock(philo->forks);
//    pthread_mutex_unlock(philo->forks);
//    philo->status = SLEEPING;
//}

//void	sleeping(t_philo *philo)
//{
//    print_status(philo, SLEEPING);
//    ft_usleep(philo->sleep_time);
//    philo->status = THINKING;
//}

//void	thinking(t_philo *philo)
//{
//    print_status(philo, THINKING);
//    if (philo->eat_max != -1 && philo->eat_cont == philo->eat_max)
//        philo->status = DEAD;
//    else
//        philo->status = EATING;
//}

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
