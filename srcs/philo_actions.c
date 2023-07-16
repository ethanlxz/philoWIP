/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:21:22 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/14 17:52:27 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	grab_forks(t_philo *p)
{
	pthread_mutex_lock(p->m_fork);
	philo_speak(p, STR_FORK);
	pthread_mutex_lock(p->next->m_fork);
	philo_speak(p, STR_FORK);
}

void	return_forks(t_philo *p)
{
	pthread_mutex_unlock(p->m_fork);
	pthread_mutex_unlock(p->next->m_fork);
}

void	philo_eat(t_philo *p)
{
	pthread_mutex_lock(p->m_eat);
	++p->total_ate;
	if (p->total_ate == p->info->min_eat)
		++p->info->met_quota;
	if (p->info->met_quota < p->info->philos)
		philo_speak(p, STR_EAT);
	p->last_ate = get_time();
	ft_usleep(p->info->eat_time);
	pthread_mutex_unlock(p->m_eat);
}

void	philo_sleep(t_philo *p)
{
	philo_speak(p, STR_SLEEP);
	ft_usleep(p->info->sleep_time);
}

void	philo_speak(t_philo *p, char *msg)
{
	pthread_mutex_lock(p->m_print);
	printf("%04i %i %s\n", get_time(), p->id, msg);
	pthread_mutex_unlock(p->m_print);
}

