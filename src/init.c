/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:16:39 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/12 20:28:19 by ka-tan           ###   ########.fr       */
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

void	init_philo(t_shell *shell, char **env)
{
	shell->debug = 0;
	shell->ast = NULL;
	shell->tokens = NULL;
	shell->status = 0;
	shell->should_exit = 0;
	shell->exit_code = 0;
	shell->env = dup_env(env);
	shell->export = dup_env(env);
	if (!shell->env || !shell->export)
		exit(EXIT_FAILURE);
}

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