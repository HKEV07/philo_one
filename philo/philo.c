/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:16:44 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/31 15:51:27 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->lock);
	pthread_mutex_destroy(&philo->data->print);
	pthread_mutex_destroy(&philo->data->time);
	while (philo)
	{
		pthread_mutex_destroy(&philo->forks);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
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

void	init_data(t_data **node, char **av)
{
	t_data	*data;

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

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_data		*data;

	if (ac < 5 || ac > 6)
		return (1);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		if (ft_check_arg(av + 1) == -1)
			return (0);
		init_data(&data, av + 1);
		philo = ft_add_philo(data);
		ft_make_circular(philo);
		pthread_mutex_init(&philo->data->time, NULL);
		pthread_mutex_init(&philo->data->print, NULL);
		pthread_mutex_init(&philo->data->lock, NULL);
		ft_int_mutex(philo);
		ft_destroy_mutex(philo);
	}
	return (0);
}
