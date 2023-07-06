/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:14:25 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/05 15:56:55 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_info
{
	int	philos;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	min_eat;
	int	met_quota;
	int	state;
}	t_info;

// init.c
int	init_val(int ac, char **av, t_info *info);

// utils.c
int	ft_atoi(const char *str);
#endif