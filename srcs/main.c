/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:52:39 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/05 16:00:10 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo(int ac, char **av)
{
	t_info	*info;

	if (!init_val(ac, av, info))
	{
		printf("Invalid parameters!");
	}
	
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		philo(ac, av);
	}
	else
		printf("Too much or too less arguments! Try again.");
	return (0);
}
