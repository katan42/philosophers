/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 22:49:14 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//mutex protects writing the stop flag
void	set_stop_flag(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

//lock, read a copy, unlock, return value of stop
int	shld_stop(t_table *table)
{
	int	stop;

	pthread_mutex_lock(&table->stop_mutex);
	stop = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (stop);
}

//checks if a philo has exceeded time_to_die
static int	philo_is_dead(t_philo *philo)
{
	long	time_now;
	long	time_last_eaten;
	int		is_dead;

	pthread_mutex_lock(&philo->meal_mutex);
	time_last_eaten = philo -> last_meal_time;
	pthread_mutex_unlock(&philo->meal_mutex);
	time_now = get_time_ms();
	is_dead = (time_now - time_last_eaten) > philo->table->time_to_die;
	return (is_dead);
}

//check if all jiak-bak-alrd
static int	all_ate_enough(t_table *table)
{
	int	i;
	int	nbr_meals_ate;

	if (table->must_eat_count < 0)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].meal_mutex);
		nbr_meals_ate = table->philo[i].meals_eaten;
		pthread_mutex_unlock(&table->philo[i].meal_mutex);
		if (nbr_meals_ate < table->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

//need to first check that all philos are alive then see if they ate enough
void	*monitor_loop(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!shld_stop(table))
	{
		i = 0;
		while (i < table->num_philos)
		{
			if (philo_is_dead(&table->philo[i]))
			{
				print_state(&table->philo[i], "died");
				set_stop_flag(table);
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(table))
		{
			set_stop_flag(table);
			return (NULL);
		}
		do_sleep(&table->philo[i], 500);
	}
	return (NULL);
}
