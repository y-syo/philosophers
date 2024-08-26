/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:39:54 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/26 15:52:47 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	is_alive(t_philo *philo)
{
	if (!(check_mutex(&(philo->data->alive_mutex), &philo->data->alive)))
		return (-1);
	if (philo->saturation < 0 || !check_mutex(&(philo->data->num_philo_mutex),
			&(philo->data->number_of_philo)))
	{
		pthread_mutex_lock(&(philo->data->alive_mutex));
		philo->data->alive = 0;
		pthread_mutex_unlock(&(philo->data->alive_mutex));
		if (check_mutex(&(philo->data->num_philo_mutex),
				&(philo->data->number_of_philo)))
		{
			pthread_mutex_lock(&(philo->data->print_mutex));
			printf(DIED_STR, get_time(philo->data->start_time), philo->id);
			pthread_mutex_unlock(&(philo->data->print_mutex));
		}
		return (-1);
	}
	return (0);
}

void	set_meal_number(t_philo *philo)
{
	if (philo->number_of_meal > 0)
		philo->number_of_meal--;
	if (philo->number_of_meal == 0)
	{
		pthread_mutex_lock(&(philo->data->num_philo_mutex));
		philo->data->number_of_philo -= 1;
		pthread_mutex_unlock(&(philo->data->num_philo_mutex));
		philo->number_of_meal--;
	}
}
