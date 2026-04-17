/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/17 21:18:02 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void parse_table_args(t_table *table, char **argv)
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

int	init_table(t_table *table, char **argv)
{
	int i;

	parse_table_args(table, argv);
	table->stop = 0;
	table->start_time = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (1);
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philo)
		return (1);
	return (0);
}

int	init_philos(t_table *table, t_philo *philo)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		table->philo[i].id = i + 1; // because first philo is 1
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = 0;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		table->philo[i].table = table;
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		i++;
	}
}

/* void ft_strarr_free(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_shell(t_shell *shell)
{
	ft_strarr_free(shell->env);
	ft_strarr_free(shell->export);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->tokens)
		free_token_list(shell->tokens);
} */

void	cleanup(t_table *table)
{
	int i;

	i = 0;
	while(i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->stop_mutex);
	free(table->forks);
	free(table->philo);
}
