/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:43:22 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/28 19:26:31 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_check_died(t_philo *philo)
{
	sem_wait(philo->data->died);
	if (philo->data->nbr_philo == 1)
		ft_usleep(philo->data->time_to_die, philo);
	if (philo->next_eat <= ft_time_msc())
	{
		sem_wait(philo->data->print);
		printf("%lld %d died\n", \
		ft_time_msc() - philo->data->start, philo->ph_id);
		sem_post(philo->data->parent_pr);
		ft_unlink_sem(philo, 1);
		exit(0);
	}
	sem_post(philo->data->died);
}

void	ft_usleep(int t, t_philo *philo)
{
	long long	time;

	time = ft_time_msc();
	while (ft_time_msc() - time < t)
	{
		usleep(100);
		if (philo->data->nbr_philo > 1)
		{
			ft_check_died(philo);
			sem_wait(philo->data->died);
			if (philo->data->nbr_time_to_eat != -1)
			{
				if (philo->nbr_eat > philo->data->nbr_time_to_eat)
				{
					sem_wait(philo->data->print);
					sem_post(philo->data->parent_pr);
					ft_unlink_sem(philo, 1);
					exit(0);
				}
			}
			sem_post(philo->data->died);
		}
	}
}

void	ft_print_message(t_philo *philo, char *str)
{
	sem_wait(philo->data->print);
	printf("%lld %d %s\n", \
	ft_time_msc() - philo->data->start, philo->ph_id, str);
	sem_post(philo->data->print);
}

void	ft_philo_life(t_philo *philo)
{
	philo->next_eat = ft_time_msc() + philo->data->time_to_die;
	if (philo->ph_id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo);
	while (1)
	{
		sem_wait(philo->data->forks);
		ft_print_message(philo, "has taken a fork");
		if (philo->data->nbr_philo == 1)
			ft_check_died(philo);
		sem_wait(philo->data->forks);
		ft_print_message(philo, "has taken a fork");
		philo->nbr_eat++;
		philo->next_eat = ft_time_msc() + philo->data->time_to_die;
		ft_print_message(philo, "is eating");
		ft_usleep(philo->data->time_to_eat, philo);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		ft_print_message(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, philo);
		ft_print_message(philo, "is thinking");
		if (philo->data->time_to_eat > philo->data->time_to_sleep)
			ft_usleep(philo->data->time_to_eat - \
			philo->data->time_to_sleep, philo);
	}
}

void	ft_int_pr(t_philo *philo)
{
	philo->data->start = ft_time_msc();
	while (philo)
	{
		philo->pr_philo = fork();
		if (philo->pr_philo < 0)
		{
			ft_kill_pr(philo);
			ft_free(philo);
		}
		if (philo->pr_philo == 0)
			ft_philo_life(philo);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
}
