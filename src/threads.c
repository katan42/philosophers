/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 23:10:18 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//+1 so that can slp through monitor check dead
static void	*lone_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	do_sleep(philo, philo->table->time_to_die + 1);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

//loop through all the philos and create thread
//if pthread_create fails halfway, some threads are already running.
//cannot just return and free everything immediately, as those threads 
//may still access freed resources
//so wait for alrd-created thread to finish with thread_join
int creating_threads(t_table *table)
{
	int i;

	table->start_time = get_time_ms();
	if (pthread_create(&table->monitor_thread, NULL, monitor_loop, table) != 0)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].thread, NULL, routine,
			&table->philo[i]) != 0)
		{
			set_stop_flag(table);
			while (i > 0)
			{
				i--;
				pthread_join(table->philo[i].thread, NULL);
			}
			pthread_join(table->monitor_thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	joining_threads(t_table *table)
{
	int i;

	if (pthread_join(table->monitor_thread, NULL) != 0)
		return (1);
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
	if (philo->table->num_philos == 1)
		return (lone_philo(philo));
	if (philo->id % 2 == 1)
		do_think(philo);
	while (!shld_stop(philo->table))
	{
		take_fork(philo);
		do_eat(philo);
		put_forks(philo);
		do_sleep(philo, philo->table->time_to_sleep);
		do_think(philo);
	}
	return (NULL);
}