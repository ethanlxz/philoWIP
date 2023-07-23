/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:57:20 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 18:46:01 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_meal(t_philo *p)
{
	pthread_mutex_lock(p->m_eat);
	if (p->info-> min_eat != 0 && p->info->met_quota >= p->info->philos)
	{
		pthread_mutex_unlock(p->m_eat);
		pthread_mutex_lock(p->m_end);
		p->info->state = END;
		pthread_mutex_unlock(p->m_end);
		return (1);
	}
	pthread_mutex_unlock(p->m_eat);
	return (0);
}

int	philo_dead(t_philo *p)
{
	pthread_mutex_lock(p->m_eat);
	if (get_time() - p->last_ate >= p->info->die_time)
	{
		pthread_mutex_unlock(p->m_eat);
		pthread_mutex_lock(p->m_end);
		p->info->state = END;
		pthread_mutex_unlock(p->m_end);
		return (1);
	}
	pthread_mutex_unlock(p->m_eat);
	return (0);
}

void	*check_philo(void *ptr)
{
	int		i;
	t_philo	*p;

	i = 0;
	p = (t_philo *)ptr;
	while (1)
	{
		if (philo_meal(&p[i % p->info->philos]))
		{
			break ;
		}
		if (philo_dead(&p[i % p->info->philos]))
		{
			pthread_mutex_lock(p->m_print);
			printf("%04i %i %s\n", get_time(), p->id, STR_DIED);
			break ;
		}
		usleep(50 * p->info->philos);
	}
	return (NULL);
}
