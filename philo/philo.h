/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:34:02 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/28 22:50:22 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long				nbr_philo;
	long				time_to_eat;
	long				time_to_die;
	long				time_to_sleep;
	long				nbr_time_to_eat;
	long long			start;
	pthread_mutex_t		lock;
	pthread_mutex_t		print;
	pthread_mutex_t		time;
}	t_data;

typedef struct s_philo
{
	pthread_t		th_philo;
	int				ph_id;
	long long		last_eat;
	int				nbr_eat;
	pthread_mutex_t	forks;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

int			ft_atoi(const char *str);
long long	ft_timemsc(void);
long long	ft_timemsc_start(t_philo *philo);
t_philo		*ft_lstnew(t_data *data, int id);
t_philo		*ft_lstlast(t_philo *lst);
t_philo		*ft_add_philo(t_data *data);
void		ft_lstadd_back(t_philo **lst, t_philo *new);
void		ft_make_circular(t_philo *philo);
void		ft_int_mutex(t_philo *philo);
void		ft_destroy_mutex(t_philo *philo);
void		ft_usleep(int t);
#endif