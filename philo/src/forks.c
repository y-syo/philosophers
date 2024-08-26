/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:38:26 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/26 16:26:53 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leave_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	*(philo->l_fork_state) = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	*(philo->r_fork_state) = 0;
	pthread_mutex_unlock(philo->r_fork);
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

int	wait_for_fork(t_philo *philo, pthread_mutex_t *fork, int *fork_state,
				unsigned long long start_time)
{
	unsigned long long	elapsed_time;

	while (check_mutex(fork, fork_state))
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

int	take_forks(t_philo *philo)
{
	if (is_alive(philo))
		return (-1);
	if (wait_for_fork(philo, philo->r_fork, philo->r_fork_state,
			get_time(philo->data->start_time)))
		return (-1);
	grab_fork(0, philo);
	if (wait_for_fork(philo, philo->l_fork, philo->l_fork_state,
			get_time(philo->data->start_time)))
		return (-1);
	grab_fork(1, philo);
	return (0);
}
