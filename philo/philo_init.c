/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:40:14 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/31 15:43:58 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", ft_timemsc_start(philo), philo->ph_id, str);
	pthread_mutex_unlock(&philo->data->print);
}

int	ft_check_died(t_philo *philo)
{
	if (philo->ph_id > 100)
		ft_usleep(philo->data->time_to_die);
	pthread_mutex_lock(&philo->data->lock);
	if (ft_timemsc_start(philo) - philo->last_eat >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->lock);
		ft_print_message(philo, "died");
		pthread_mutex_lock(&philo->data->print);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (1);
}

int	ft_check_nbr_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->nbr_time_to_eat != -1)
	{
		if (philo->nbr_eat > philo->data->nbr_time_to_eat)
			return (0);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (1);
}

void	*ft_philo_life(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)(arg);
	if (!(philo->ph_id % 2))
		ft_usleep(philo->data->time_to_eat);
	while (1)
	{	
		pthread_mutex_lock(&philo->forks);
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->next->forks);
		ft_print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->lock);
		philo->nbr_eat++;
		philo->last_eat = ft_timemsc_start(philo);
		pthread_mutex_unlock(&philo->data->lock);
		ft_print_message(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->forks);
		pthread_mutex_unlock(&philo->next->forks);
		ft_print_message(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_print_message(philo, "is thinking");
	}
	return (NULL);
}

void	ft_int_mutex(t_philo *philo)
{
	while (philo)
	{
		pthread_mutex_init(&philo->forks, NULL);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
	while (philo)
	{
		pthread_create(&philo->th_philo, NULL, ft_philo_life, philo);
		pthread_detach(philo->th_philo);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
	while (1)
	{
		if (!ft_check_nbr_eat(philo))
			break ;
		else if (!ft_check_died(philo))
			break ;
		philo = philo->next;
		usleep(100);
	}
}
