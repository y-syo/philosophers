/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:39:21 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/26 15:53:05 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, unsigned long long timestamp, t_philo *philo)
{
	if (!is_alive(philo))
	{
		pthread_mutex_lock(&(philo->data->print_mutex));
		if (check_mutex(&(philo->data->alive_mutex), &philo->data->alive))
			printf(str, timestamp, philo->id);
		pthread_mutex_unlock(&(philo->data->print_mutex));
	}
}

char	check_mutex(pthread_mutex_t *mutex, int *mutex_value)
{
	int	value;

	pthread_mutex_lock(mutex);
	value = *(mutex_value);
	pthread_mutex_unlock(mutex);
	return (value);
}
