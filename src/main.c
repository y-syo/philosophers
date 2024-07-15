/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:33 by mmoussou          #+#    #+#             */
/*   Updated: 2024/07/16 01:15:27 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *arg)
{
}

int	main(int ac, char **av)
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	(void) ac;
	(void) av;
	if (argc < 5 || argc > 6)
	{
		ft_putstr("bad usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	//if (check_args(av))
	//	return (1);
	
	return (0);
}
