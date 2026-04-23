/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/23 17:05:52 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroying_forks(t_table *table, int i)
{
	while(i > 0)
	{
		i--;
		pthread_mutex_destroy(&table->forks[i]);
		
	}
	free(table->forks);
	table->forks = NULL;
}

void	destroying_philo_mutexes(t_table *table, int i)
{
	while(i > 0)
	{
		i--;
		pthread_mutex_destroy(&table->philo[i].meal_mutex);	
	}
}

//destroy philo lock->philo->shared->forks
void	cleanup(t_table *table)
{
	destroying_philo_mutexes(table, table->num_philos);
	free(table->philo);
	table->philo = NULL;
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	destroying_forks(table, table->num_philos);
}
