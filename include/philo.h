/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:50 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/19 10:29:46 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>

# define PHILO_MAX 200

typedef struct s_data
{
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	time_die;
	unsigned int	number_of_meal;
	char			alive;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	unsigned int	saturation;
	unsigned int	number_of_meal;
	unsigned int	id;
}					t_philo;

typedef struct s_main
{
	unsigned int	number_of_philos;
	t_data			data;
	t_philo			*philos;
}				t_main;

# define FORK_STR "\x1b[36m%lld %d has taken a fork\n\x1b[0m"
# define SLEEPING_STR "\x1b[35m%lld %d is sleeping\n\x1b[0m"
# define THINKING_STR "\x1b[32m%lld %d is thinking\n\x1b[0m"
# define EATING_STR "\x1b[33m%lld %d is eating\n\x1b[0m"
# define DIED_STR "\x1b[31m%lld %d died\n\x1b[0m"

#endif
