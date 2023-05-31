/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utlis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:42:40 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/27 20:52:41 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_data(t_data **node, char **av)
{
	t_data		*data;

	data = *node;
	data->nbr_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	data->start = 0;
	if (av[4])
		data->nbr_time_to_eat = ft_atoi(av[4]);
	else
		data->nbr_time_to_eat = -1;
	data->start = 0;
}

long long	ft_time_msc(void)
{
	struct timeval		tm;

	gettimeofday(&tm, NULL);
	return (((tm.tv_sec * 1000) + (tm.tv_usec / 1000)));
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
	size_t		i;
	long		s;

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

int	ft_check_arg(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
