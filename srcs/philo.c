/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:49:23 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/06 22:24:06 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_philo(int id, t_info *info)
{

}

void	philo(t_info *info)
{
	int	id;

	id = 1;
	while (id <= info->philos)
	{
		if (!create_philo(id, info))
		{
			printf("Error!");
			return ;
		}
		id++;
	}
}
