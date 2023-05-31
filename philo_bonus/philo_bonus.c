/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:14:38 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/31 15:55:20 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_unlink_sem(t_philo *philo, int i)
{
	if (i == 0)
	{
		sem_close(philo->data->print);
		sem_close(philo->data->forks);
		sem_close(philo->data->died);
		sem_close(philo->data->parent_pr);
	}
	else
	{
		sem_unlink("/fork");
		sem_unlink("/print");
		sem_unlink("/parent_pr");
		sem_unlink("/died");
	}
}

void	ft_kill_pr(t_philo *philo)
{
	while (philo)
	{
		kill(philo->pr_philo, SIGKILL);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
}

void	ft_init_sem(t_philo *philo)
{
	ft_unlink_sem(philo, 1);
	philo->data->forks = sem_open("/fork", O_CREAT, \
	0777, philo->data->nbr_philo);
	philo->data->print = sem_open("/print", O_CREAT, 0777, 1);
	philo->data->parent_pr = sem_open("/parent_pr", O_CREAT, 0777, 0);
	philo->data->died = sem_open("/died", O_CREAT, 0777, 1);
}

void	ft_free(t_philo *philo)
{
	free(philo->data);
	while (philo)
	{
		free(philo);
		philo = philo->next;
		if (philo->ph_id == 1)
			break ;
	}
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
		ft_init_sem(philo);
		ft_int_pr(philo);
		sem_wait(philo->data->parent_pr);
		ft_kill_pr(philo);
		ft_unlink_sem(philo, 0);
		ft_free(philo);
	}
	return (0);
}
