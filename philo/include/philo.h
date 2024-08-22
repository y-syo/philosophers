/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:11:50 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/22 14:39:31 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>

# define PHILO_MAX 200

typedef struct s_data
{
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		time_die;
	unsigned int		number_of_meal;
	char				alive;
	unsigned long long	start_time;
}				t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	char			*l_fork_state;
	char			*r_fork_state;
	t_data			*data;
	long long		saturation;
	unsigned int	number_of_meal;
	unsigned int	id;
}					t_philo;

typedef struct s_main
{
	unsigned int	number_of_philos;
	t_data			data;
}				t_main;

# define FORK_STR "\x1b[1;35m%lld %d has taken a fork\n\x1b[0m"
# define SLEEPING_STR "\x1b[1;34m%lld %d is sleeping\n\x1b[0m"
# define THINKING_STR "\x1b[1;32m%lld %d is thinking\n\x1b[0m"
# define EATING_STR "\x1b[1;36m%lld %d is eating\n\x1b[0m"
# define DIED_STR "\x1b[1;31m%lld %d died\n\x1b[0m"

#endif
