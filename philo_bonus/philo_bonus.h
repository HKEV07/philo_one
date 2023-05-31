/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:10:59 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/28 19:26:27 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_data
{
	long				nbr_philo;
	long				time_to_eat;
	long				time_to_die;
	long				time_to_sleep;
	long				nbr_time_to_eat;
	long long			start;
	sem_t				*print;
	sem_t				*parent_pr;
	sem_t				*forks;
	sem_t				*died;
}	t_data;

typedef struct s_philo
{
	pid_t			pr_philo;
	int				ph_id;
	long long		next_eat;
	int				nbr_eat;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

void		ft_make_circular(t_philo *philo);
t_philo		*ft_add_philo(t_data *data);
int			ft_atoi(const char *str);
int			ft_check_arg(char **av);
long long	ft_time_msc(void);
void		ft_usleep(int t, t_philo *philo);
void		ft_print_message(t_philo *philo, char *str);
void		ft_int_pr(t_philo *philo);
void		ft_unlink_sem(t_philo *philo, int i);
void		init_data(t_data **node, char **av);
void		ft_kill_pr(t_philo *philo);
void		ft_free(t_philo *philo);
#endif