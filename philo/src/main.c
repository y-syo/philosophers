/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:33 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/26 17:07:23 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_to_die(t_philo philo)
{
	usleep(philo.data->time_die * 1000);
	print(DIED_STR, (long long) philo.data->time_die, &philo);
}

void	philo(t_main *program, t_philo *philos)
{
	unsigned int	i;

	i = 0;
	while (i < program->number_of_philos)
	{
		if (pthread_create(&(philos[i]).thread,
				NULL, philo_routine, &philos[i]))
		{
			pthread_mutex_lock(&(program->data.alive_mutex));
			program->data.alive = 0;
			pthread_mutex_unlock(&(program->data.alive_mutex));
			break ;
		}
		i++;
	}
	while (i)
	{
		i--;
		pthread_join((philos[i]).thread, NULL);
	}
}

#include <stdlib.h>

int	main(int ac, char **av)
{
	t_main			program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	//pthread_mutex_t	*forks;
	int				forks_state[PHILO_MAX];
	//int				*forks_state;

	memset(forks, 0, sizeof(pthread_mutex_t) * PHILO_MAX);
	memset(forks_state, 0, sizeof(int) * PHILO_MAX);
	//forks = calloc(sizeof(pthread_mutex_t), PHILO_MAX);
	//forks_state = calloc(sizeof(int), PHILO_MAX);
	if (ac < 5 || ac > 6)
	{
		printf("bad usage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (check_args(ac, av))
	{
		printf("error: bad arguments\n");
		return (1);
	}
	if (data_init(&program, ac, av))
		return (-1);
	philo_init(&program, philos, forks, forks_state);
	if (program.number_of_philos == 1)
		wait_to_die(philos[0]);
	else
		philo(&program, philos);
	return (0);
}
