/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoussou <mmoussou@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 22:25:13 by mmoussou          #+#    #+#             */
/*   Updated: 2024/08/23 23:03:42 by mmoussou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol(const char *str)
{
	long long	r;
	int			i;

	r = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r);
}

int	check_str(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	str_offset(char *str)
{
	int		offset;

	offset = 0;
	while (str[offset] == 32
		|| (str[offset] >= 9 && str[offset] <= 13))
		offset++;
	while (str[offset] == '0')
		offset++;
	return (offset);
}

int	verif_nb(char *str)
{
	long	atol;

	if (check_str(str))
		return (-1);
	atol = ft_atol(str);
	if (atol > 2147483647 || atol < 1
		|| ft_strlen(str + str_offset(str)) > 10)
		return (-1);
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (verif_nb(av[i]))
			return (-1);
		i++;
	}
	if (ft_atoi(av[1]) > 200)
		return (-1);
	return (0);
}
