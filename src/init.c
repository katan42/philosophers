/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/16 17:04:29 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

typedef struct s_table // whole restaurant; stores info that philos need to know
{
	int             num_philos;
	long            time_to_die;
	long            time_to_eat;
	long            time_to_sleep;
	int             must_eat_count;
	int             stop;

	long            start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;
	pthread_mutex_t stop_mutex;
	struct s_philo	*philos;
}	t_table;

typedef struct s_philo // stores things specific to 1 philos
{
	int             id;
	int             meals_eaten;
	long            last_meal_time;

	pthread_t       thread;
	pthread_mutex_t meal_mutex;

	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	t_table           *table;
}	t_philo;

void	init_table(t_table *table, char **argv)
{
	int i;

	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->stop = 0;
	table->start_time = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return ;
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->stop_mutex, NULL);
	table->philo = malloc(sizeof(t_philo) * table->num_philos);
	
}

void	init_philos(t_philo *philo)

void	ft_strarr_free(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_shell(t_shell *shell)
{
	ft_strarr_free(shell->env);
	ft_strarr_free(shell->export);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->tokens)
		free_token_list(shell->tokens);
}