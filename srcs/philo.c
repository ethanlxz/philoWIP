/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:49:23 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/21 00:21:39 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void	*check_philo(void *ptr)
// {
// 	int		i;
// 	t_philo	*p;

// 	i = 0;
// 	p = (t_philo *)ptr;
// 	while (1)
// 	{
// 		if (philo_meal(&p[i % p->info->philos]))
// 		{
// 			break ;
// 		}
// 		if (philo_dead(&p[i % p->info->philos]))
// 		{
// 			pthread_mutex_lock(p->m_print);
// 			printf("%04i %i %s\n", get_time(), p->id, STR_DIED);
// 			break ;
// 		}
// 		usleep(50);
// 	}
// 	return (NULL);
// }

static	void	*philo_brain(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if (p->id % 2 == 0)
		ft_usleep(p->info->eat_time / 2);
	while (true)
	{
		pthread_mutex_lock(p->m_end);
		if (p->info->state == END)
		{
			pthread_mutex_unlock(p->m_eat);
			pthread_mutex_unlock(p->m_end);
			break ;
		}
		pthread_mutex_unlock(p->m_end);
		grab_forks(p);
		philo_eat(p);
		return_forks(p);
		philo_sleep(p);
		philo_speak(p, STR_THINK);
	}
	return (NULL);
}

static int	create_th(t_info *info, t_philo *philo)
{
	int			i;
	pthread_t	*th;
	pthread_t	check;

	th = malloc(sizeof(pthread_t) * info->philos);
	if (th == NULL)
		return (1);
	i = -1;
	while (++i < info->philos)
	{
		if (pthread_create(&th[i], NULL, &philo_brain, (void *)&philo[i]) != 0)
			return (1);
	}
	i = -1;
	pthread_create(&check, NULL, &check_philo, (void *)philo);
	pthread_join(check, NULL);
	while (++i < info->philos)
		pthread_join(th[i], NULL);
	mutex_destroy(info, philo);
	free (th);
	return (free(info->m_print), free(info->m_eat), free(info->m_fork),
		free(info->m_end), free(info->philo_strc), free(info->m_quota), 0);
}

static t_philo	init_philo(int id, t_info	*info,
	pthread_mutex_t *fork)
{
	t_philo	philo;

	philo.id = id + 1;
	philo.info = info;
	philo.m_print = info->m_print;
	philo.last_ate = 0;
	philo.total_ate = 0;
	philo.m_eat = info->m_eat;
	philo.m_end = info->m_end;
	philo.m_quota = info->m_quota;
	philo.l_fork = &fork[id];
	philo.r_fork = &fork[(id + 1) % info->philos];
	return (philo);
}

	// info->m_print = malloc(sizeof(pthread_mutex_t));
	// if (!info->m_print || pthread_mutex_init(info->m_print, NULL) != 0)
	// 	return (NULL);
	// info->m_eat = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(info->m_eat, NULL);
	// info->m_end = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(info->m_end, NULL);
	// info->m_quota = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(info->m_quota, NULL);
static t_philo	*create_philo(t_info *info)
{
	int				id;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if (mutex_init(info) == 1)
		return (NULL);
	fork = malloc(sizeof(pthread_mutex_t) * info->philos);
	info->m_fork = fork;
	id = -1;
	while (++id < info->philos)
		pthread_mutex_init(&fork[id], NULL);
	id = -1;
	philo = malloc(sizeof(t_philo) * info->philos);
	info->philo_strc = philo;
	while (++id < info->philos)
	{
		philo[id] = init_philo(id, info, fork);
		if (philo == NULL)
			return (NULL);
	}
	return (philo);
}

int	philo(t_info *info)
{
	t_philo			*philo;

	info->state = THINKING;
	philo = create_philo(info);
	if (!philo)
		return (1);
	create_th(info, philo);
	return (0);
}
