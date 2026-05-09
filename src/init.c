/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 20:38:45 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	parse_table_args(t_table *table, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
}

int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (1);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroying_forks(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_table(t_table *table, char **argv)
{
	parse_table_args(table, argv);
	table->stop = 0;
	table->start_time = 0;
	if (init_forks(table))
		return (1);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (destroying_forks(table, table->num_philos), 1);
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
	{
		destroying_forks(table, table->num_philos);
		pthread_mutex_destroy(&table->print_mutex);
		return (1);
	}
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
	{
		destroying_forks(table, table->num_philos);
		pthread_mutex_destroy(&table->print_mutex);
		pthread_mutex_destroy(&table->stop_mutex);
		return (1);
	}
	return (0);
}

//philo id = i+1 as 1st philo is 1
int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		table->philo[i].table = table;
		if (pthread_mutex_init(&table->philo[i].meal_mutex, NULL) != 0)
		{
			destroying_philo_mutexes(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}
