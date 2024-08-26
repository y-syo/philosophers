/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:39:04 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/26 16:32:39 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_main *program, int ac, char **av)
{
	struct timeval	tv;

	program->number_of_philos = ft_atoi(av[1]);
	program->data.time_die = ft_atoi(av[2]);
	program->data.time_eat = ft_atoi(av[3]);
	program->data.time_sleep = ft_atoi(av[4]);
	program->data.alive = 1;
	program->data.number_of_meal = -1;
	program->data.number_of_philo = -1;
	if (ac == 6)
	{
		program->data.number_of_meal = ft_atoi(av[5]);
		program->data.number_of_philo = ft_atoi(av[1]);
	}
	if (gettimeofday(&tv, NULL))
		return (-1);
	program->data.start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	pthread_mutex_init(&(program->data.print_mutex), 0);
	pthread_mutex_init(&(program->data.alive_mutex), 0);
	pthread_mutex_init(&(program->data.num_philo_mutex), 0);
	return (0);
}

void	philo_init(t_main *program, t_philo *philos,
				pthread_mutex_t *forks, int *forks_state)
{
	unsigned int	i;

	i = program->number_of_philos;
	memset(forks, 0, sizeof(pthread_mutex_t) * i);
	memset(forks_state, 0, sizeof(char) * i);
	while (i)
	{
		i--;
		philos[i].l_fork = &(forks[i]);
		if (i + 1 == program->number_of_philos)
			philos[i].r_fork = &(forks[0]);
		else
			philos[i].r_fork = &(forks[i + 1]);
		philos[i].l_fork_state = &(forks_state[i]);
		if (i + 1 == program->number_of_philos)
			philos[i].r_fork_state = &(forks_state[0]);
		else
			philos[i].r_fork_state = &(forks_state[i + 1]);
		philos[i].saturation = program->data.time_die;
		philos[i].number_of_meal = program->data.number_of_meal;
		philos[i].data = &(program->data);
		philos[i].id = i + 1;
	}
}
