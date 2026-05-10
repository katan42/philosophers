/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:14:43 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/10 10:21:32 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static long	check_sign_and_skip(size_t *i, const char *str, long sign)
{
	while ((str[*i] == 32) || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = sign * -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	long	sign;

	i = 0;
	result = 0;
	sign = 1;
	sign = check_sign_and_skip(&i, str, sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX / 10
			|| (result == INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10))
		{
			if (sign == 1)
				return (INT_MAX);
			return (INT_MIN);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
