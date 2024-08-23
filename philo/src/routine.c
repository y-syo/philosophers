/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:39:38 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/23 14:42:33 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	set_meal_number(philo);
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
