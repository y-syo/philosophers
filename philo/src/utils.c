/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:40:04 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/23 22:55:09 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	const char	*endptr;

	endptr = s;
	while (*endptr)
		endptr++;
	return (endptr - s);
}

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

unsigned long long	get_time(unsigned long long start_time)
{
	struct timeval		tv;
	unsigned long long	actual_time;

	gettimeofday(&tv, NULL);
	actual_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (actual_time - start_time);
}
