/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:33 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/23 14:32:59 by mmoussou         ###   ########.fr       */
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
	memset(forks, 0, sizeof(pthread_mutex_t) * PHILO_MAX);
	memset(forks_state, 0, sizeof(char) * PHILO_MAX);
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

void	print(char *str, unsigned long long timestamp, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print_mutex));
	printf(str, timestamp, philo->id);
	pthread_mutex_unlock(&(philo->data->print_mutex));
}

char	check_mutex(pthread_mutex_t *mutex, int *mutex_value)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *(mutex_value);
	pthread_mutex_unlock(mutex);
	return (value);
}

void	wait_to_die(t_philo philo)
{
	usleep(philo.data->time_die * 1000);
	print(DIED_STR, (long long) philo.data->time_die, &philo);
}

unsigned long long	get_time(unsigned long long start_time)
{
	struct timeval		tv;
	unsigned long long	actual_time;

	gettimeofday(&tv, NULL);
	actual_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (actual_time - start_time);
}

unsigned long long	is_alive(t_philo *philo)
{
	if (!(check_mutex(&(philo->data->alive_mutex), &philo->data->alive)))
		return (-1);
	if (philo->saturation < 0 || !check_mutex(&(philo->data->num_philo_mutex),
			&(philo->data->number_of_philo)))
	{
		if (check_mutex(&(philo->data->num_philo_mutex),
				&(philo->data->number_of_philo)))
			print(DIED_STR, get_time(philo->data->start_time), philo);
		pthread_mutex_lock(&(philo->data->alive_mutex));
		philo->data->alive = 0;
		pthread_mutex_unlock(&(philo->data->alive_mutex));
		return (-1);
	}
	return (0);
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	*(philo->l_fork_state) = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*(philo->r_fork_state) = 0;
	pthread_mutex_unlock(philo->r_fork);
}

void	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	*(philo->l_fork_state) = 1;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*(philo->r_fork_state) = 1;
	pthread_mutex_unlock(philo->r_fork);
	print(FORK_STR, get_time(philo->data->start_time), philo);
	print(FORK_STR, get_time(philo->data->start_time), philo);
}

void	grab_fork(char mode, t_philo *philo)
{
	if (mode)
	{
		pthread_mutex_lock(philo->l_fork);
		*(philo->l_fork_state) = 1;
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		*(philo->r_fork_state) = 1;
		pthread_mutex_unlock(philo->r_fork);
	}
	print(FORK_STR, get_time(philo->data->start_time), philo);
}

int	take_forks(t_philo *philo)
{
	unsigned long long	start_time;
	unsigned long long	elapsed_time;

	start_time = get_time(philo->data->start_time);
	if (is_alive(philo))
		return (-1);
	while (check_mutex(philo->r_fork, philo->r_fork_state))
	{
		usleep(100);
		if (is_alive(philo))
			return (-1);
		elapsed_time = get_time(philo->data->start_time);
		philo->saturation -= elapsed_time - start_time;
		start_time = elapsed_time;
	}
	grab_fork(0, philo);
	while (check_mutex(philo->l_fork, philo->l_fork_state))
	{
		usleep(100);
		if (is_alive(philo))
			return (-1);
		elapsed_time = get_time(philo->data->start_time);
		philo->saturation -= elapsed_time - start_time;
		start_time = elapsed_time;
	}
	grab_fork(1, philo);
	return (0);
}

int	eating(t_philo *philo)
{
	unsigned long long	elapsed_time;
	unsigned long long	start_time;
	unsigned long long	end_time;

	start_time = get_time(philo->data->start_time);
	print(EATING_STR, start_time, philo);
	end_time = start_time + philo->data->time_eat;
	philo->saturation = philo->data->time_die;
	while (get_time(philo->data->start_time) < end_time)
	{
		usleep(100);
		if (is_alive(philo))
		{
			leave_forks(philo);
			return (-1);
		}
		elapsed_time = get_time(philo->data->start_time);
		philo->saturation -= elapsed_time - start_time;
		start_time = elapsed_time;
	}
	leave_forks(philo);
	if (philo->number_of_meal > 0)
		philo->number_of_meal--;
	if (philo->number_of_meal == 0)
	{
		pthread_mutex_lock(&(philo->data->num_philo_mutex));
		philo->data->number_of_philo -= 1;
		pthread_mutex_unlock(&(philo->data->num_philo_mutex));
		philo->number_of_meal--;
	}
	return (0);
}

int	sleeping(t_philo *philo)
{
	unsigned long long	end_time;
	unsigned long long	start_time;
	unsigned long long	elapsed_time;

	start_time = get_time(philo->data->start_time);
	print(SLEEPING_STR, start_time, philo);
	end_time = start_time + philo->data->time_sleep;
	while (get_time(philo->data->start_time) < end_time)
	{
		usleep(100);
		if (is_alive(philo))
			return (-1);
		elapsed_time = get_time(philo->data->start_time);
		philo->saturation -= elapsed_time - start_time;
		start_time = elapsed_time;
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	if (is_alive(philo))
		return (-1);
	print(THINKING_STR, get_time(philo->data->start_time), philo);
	if (take_forks(philo))
		return (-1);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 1)
		usleep(500);
	take_forks(philo);
	while (!is_alive(philo))
	{
		if (eating(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (NULL);
}

void	philo(t_main program, t_philo *philos)
{
	unsigned int	i;

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
	int				forks_state[PHILO_MAX];

	if (ac < 5 || ac > 6)
	{
		printf("bad usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	//if (check_args(av))
	//	return (1);
	if (data_init(&program, ac, av))
		return (-1);
	philo_init(&program, philos, forks, forks_state);
	if (program.number_of_philos == 1)
		wait_to_die(philos[0]);
	else
		philo(program, philos);
	return (0);
}
