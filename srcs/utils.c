/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martina <martina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:10:51 by martina           #+#    #+#             */
/*   Updated: 2023/09/05 15:41:32 by martina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t	get_time(void)
{
    struct timeval	tv;
    u_int64_t		time;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

//int     error(char *str, t_data *t_data)
//{
//    printf("%s\n", str);
//    if (t_data)
//        ft_exit(t_data);
//    return (1);
//}

int	ft_atoi(const char *str)
{
    int		i;
    int		sign;
    long	nb;

    i = 0;
    sign = 1;
    nb = 0;
    while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
            || str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
        i++;
    if (str[i] && (str[i] == '-' || str[i] == '+'))
        if (str[i++] == '-')
            sign = -1;
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
        nb = (nb * 10) + (str[i++] - '0');
    return (nb * sign);
}

int	ft_strlen(char *str)
{
    int	i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
    int	i;

    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


