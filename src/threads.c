/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/17 21:30:52 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//loop through all the philos and create thread
int creating_threads(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL, routine,
			&table->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	joining_threads(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!sim_shld_stop(philo->table))
	{
		//take fork
		//eat
		//put fork
		//sleep
		//think
	}
	return (NULL);
}