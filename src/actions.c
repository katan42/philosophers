/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:10:29 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 22:52:22 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//alternate odd even take fork so no deadlock
void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

//lock to write timing, increment; unlock then print as printf slow
void	do_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	do_sleep(philo, philo->table->time_to_eat);
}

//as usleep is a slp at least time, & nt slp exactly
void	do_sleep(t_philo *philo, long slp_duration)
{
	long	time_to_wake;

	time_to_wake = get_time_ms() + slp_duration;
	while (!shld_stop(philo->table))
	{
		if (get_time_ms() >= time_to_wake)
			break ;
		usleep(500);
	}
}

void	do_think(t_philo *philo)
{
	print_state(philo, "is thinking");
	if ((philo->table->num_philos % 2 == 1) && (philo->id % 2 == 1))
		usleep(500);
}