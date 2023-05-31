/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_add_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:42:22 by ibenaait          #+#    #+#             */
/*   Updated: 2023/05/24 20:47:50 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_make_circular(t_philo *philo)
{
	t_philo		*head;

	head = philo;
	while (philo->next != NULL)
		philo = philo->next;
	philo->next = head;
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_philo	*ft_lstnew(t_data *data, int id)
{
	t_philo		*node;

	node = malloc(sizeof(t_philo));
	if (!node)
		return (0);
	node->ph_id = id;
	node->data = data;
	node->nbr_eat = 0;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo		*last;

	if (lst)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
}

t_philo	*ft_add_philo(t_data *data)
{
	int			i;
	t_philo		*list;

	i = 0;
	list = NULL;
	while (i < data->nbr_philo)
	{
		ft_lstadd_back(&list, ft_lstnew(data, i + 1));
		i++;
	}
	return (list);
}
