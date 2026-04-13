/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:50:08 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/13 15:18:55 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo t_philo;
typedef struct s_table t_table;
struct s_table // whole restaurant; stores info that philos need to know
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
	t_philo			*philos;
};

struct s_philo // stores things specific to 1 philos
{
	int             id;
	int             meals_eaten;
	long            last_meal_time;

	pthread_t       thread;
	pthread_mutex_t meal_mutex;

	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	t_table           *table;
};



#endif
