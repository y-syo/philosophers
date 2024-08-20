/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:33 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/20 12:51:05 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		r;
	int		i;
	char	s;

	r = 0;
	i = 0;
	s = 1;
	if (!str)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r * s);
}

void	data_init(t_main *program, int ac, char **av)
{
	program->number_of_philos = ft_atoi(av[1]);
	program->data.time_die = ft_atoi(av[2]);
	program->data.time_eat = ft_atoi(av[3]);
	program->data.time_sleep = ft_atoi(av[4]);
	program->data.alive = 1;
	program->data.number_of_meal = -1;
	if (ac == 6)
		program->data.number_of_meal = ft_atoi(av[5]);
}

void	philo_init(t_main *program, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = program->number_of_philos;
	while (i)
	{
		i--;
		philos[i].l_fork = &(forks[i]);
		if (i + 1 == program->number_of_philos)
			philos[i].r_fork = &(forks[0]);
		else
			philos[i].r_fork = &(forks[i + 1]);
		philos[i].saturation = program->data.time_die;
		philos[i].number_of_meal = program->data.number_of_meal;
		philos[i].data = &(program->data);
	}
}

void	wait_to_die(t_philo philo)
{
	printf(DIED_STR, (long long) philo.data->time_die, philo.id);
}

	// ------------------------------------------------------------------------------------------------------------------------------------------

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;

	return (NULL);
}

	// ------------------------------------------------------------------------------------------------------------------------------------------

void	philo(t_main program, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < program.number_of_philos)
	{
		pthread_create(&(philos[i]).thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < program.number_of_philos)
	{
		pthread_join((philos[i]).thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_main			program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac < 5 || ac > 6)
	{
		printf("bad usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	//if (check_args(av))
	//	return (1);
	data_init(&program, ac, av);
	philo_init(&program, philos, forks);
	if (program.number_of_philos == 1)
		wait_to_die(philos[0]);
	else
		philo(program, philos);
	return (0);
}
