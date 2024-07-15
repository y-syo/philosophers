/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:50 by mmoussou          #+#    #+#             */
/*   Updated: 2024/07/16 00:30:21 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				running;
	uint			time_to_die;
	uint			time_to_eat;
	uint			time_to_sleep;
	uint			*number_of_philos;
	int				number_of_meals;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_main
{
	uint	number_of_philos;
	t_philo	*philos;
}				t_main;

#endif
