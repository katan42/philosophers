/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:14:55 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/10 15:25:17 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	is_positive_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//L suffix makes it explicit & keeps it long aft multiplying(avoids overflow)
//The literal 1000 w/o a suffix is an int
long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

//confirm sim cont bef print
void	print_state(t_philo *philo, char *str)
{
	t_table	*table;
	long	sim_time;

	table = philo->table;
	sim_time = get_time_ms() - table->start_time;
	pthread_mutex_lock(&table->print_mutex);
	if (!shld_stop(table))
		printf("%ld %d %s\n", sim_time, philo->id, str);
	pthread_mutex_unlock(&table->print_mutex);
	return ;
}
