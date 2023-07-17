/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:49:23 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/17 16:31:03 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*check_philo(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(p->m_eat);
		if (get_time() - p->last_ate >= p->info->die_time)
			break ;
		pthread_mutex_unlock(p->m_eat);
		ft_usleep(1);
	}
	philo_speak(p, STR_DIED);
	pthread_mutex_lock(p->m_print);
	p->info->state = END;
	return (NULL);
}

static	void	*philo_brain(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (p->id % 2 == 0)
		ft_usleep(p->info->eat_time);
	while (p->info->state == 1)
	{
		grab_forks(p);
		philo_eat(p);
		return_forks(p);
		philo_sleep(p);
		philo_speak(p, STR_THINK);
	}
	return (NULL);
}

static int	create_mtx_th(pthread_t *th, t_philo *philo)
{
	if (!init_mutex(philo))
		return (1);
	if (pthread_create(th, NULL, &check_philo, (void *)philo) != 0)
		return (1);
	if (pthread_create(th, NULL, &philo_brain, (void *)philo) != 0)
		return (1);
	return (0);
}

static int	create_philo(int id, t_info	*info, pthread_mutex_t	*m_print)
{
	static t_philo	*philo;
	t_philo			*next;
	pthread_t		th;

	next = malloc(sizeof(t_philo));
	if (!next)
		return (0);
	if (!philo)
		philo = next;
	next->next = philo->next;
	philo->next = next;
	philo = next;
	philo->id = id;
	philo->info = info;
	philo->m_print = m_print;
	philo->last_ate = 0;
	philo->total_ate = 0;
	if (create_mtx_th(&th, philo))
		return (1);
	return (0);

}

int	philo(t_info *info)
{
	int				id;
	pthread_mutex_t	*m_print;

	m_print = malloc(sizeof(pthread_mutex_t));
	if (!m_print || pthread_mutex_init(m_print, NULL) != 0)
		return (1);
	id = 1;
	info->state = THINKING;
	while (id <= info->philos)
	{
		if (create_philo(id, info, m_print))
			return (1);
		id++;
	}
	check_state(info);
	return (0);
}
