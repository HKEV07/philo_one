/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:08:59 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/28 22:50:32 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_timemsc(void)
{
	struct timeval		tm;

	gettimeofday(&tm, NULL);
	return (((tm.tv_sec * 1000) + (tm.tv_usec / 1000)));
}

long long	ft_timemsc_start(t_philo *philo)
{
	struct timeval		tm;
	static long long	time;

	gettimeofday(&tm, NULL);
	pthread_mutex_lock(&philo->data->time);
	if (time == 0)
		time = ((tm.tv_sec * 1000) + (tm.tv_usec / 1000));
	pthread_mutex_unlock(&philo->data->time);
	return (((tm.tv_sec * 1000) + (tm.tv_usec / 1000)) - time);
}

void	ft_usleep(int t)
{
	long long	time;

	time = ft_timemsc();
	while (ft_timemsc() - time < t)
		usleep(100);
}

static long	pl_m(const char *s, size_t j)
{
	long	p;
	int		m;

	p = 0;
	m = 0;
	while (s[j])
	{
		if (s[j] < '0' || s[j] > '9')
			return (-1);
		p = (p * 10) + (s[j] - '0');
		j++;
		m++;
	}
	return (p);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	s;

	i = 0;
	s = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == ' ' \
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	s = pl_m(str, i);
	if (s == 0)
		return (-1);
	return (s);
}
