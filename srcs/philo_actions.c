/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:21:22 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 18:45:44 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	grab_forks(t_philo *p)
{
	pthread_mutex_lock(p->l_fork);
	philo_speak(p, STR_FORK);
	if (p->info->philos == 1)
	{
		pthread_mutex_lock(p->m_end);
		p->info->state = END;
		pthread_mutex_unlock(p->m_end);
		return (1);
	}
	pthread_mutex_lock(p->r_fork);
	philo_speak(p, STR_FORK);
	return (0);
}

void	return_forks(t_philo *p)
{
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	philo_eat(t_philo *p)
{
	++p->total_ate;
	if (p->total_ate == p->info->min_eat)
	{
		pthread_mutex_lock(p->m_quota);
		++p->info->met_quota;
		pthread_mutex_unlock(p->m_quota);
	}
	if (p->info->met_quota <= p->info->philos)
		philo_speak(p, STR_EAT);
	pthread_mutex_lock(p->m_eat);
	p->last_ate = get_time();
	pthread_mutex_unlock(p->m_eat);
	ft_usleep(p->info->eat_time, p->info->philos);
}

void	philo_sleep(t_philo *p)
{
	philo_speak(p, STR_SLEEP);
	ft_usleep(p->info->sleep_time, p->info->philos);
}

void	philo_speak(t_philo *p, char *msg)
{
	int	tmp;

	pthread_mutex_lock(p->m_end);
	tmp = p->info->state;
	pthread_mutex_unlock(p->m_end);
	if (tmp == END)
		return ;
	pthread_mutex_lock(p->m_print);
	printf("%04i %i %s\n", get_time(), p->id, msg);
	pthread_mutex_unlock(p->m_print);
}
