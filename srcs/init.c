/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:26:20 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/21 00:11:35 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_val(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || i > 10)
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	init_val(int ac, char **av, t_info *info)
{
	if (!check_val(av[1]) || !check_val(av[2]) || !check_val(av[3])
		|| !check_val(av[4]) || (ac == 6 && !check_val(av[5])))
		return (0);
	info->philos = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->min_eat = ft_atoi(av[5]);
	else
		info->min_eat = 0;
	info->met_quota = 0;
	if (info->philos <= 0 || info->die_time <= 0
		|| info->eat_time <= 0 || info->sleep_time <= 0
		|| (ac == 6 && info->min_eat <= 0))
		return (0);
	return (1);
}

bool	mutex_init(t_info *info)
{
	info->m_print = malloc(sizeof(pthread_mutex_t));
	if (!info->m_print || pthread_mutex_init(info->m_print, NULL) != 0)
		return (1);
	info->m_eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info->m_eat, NULL);
	info->m_end = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info->m_end, NULL);
	info->m_quota = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(info->m_quota, NULL);
	return (0);
}
