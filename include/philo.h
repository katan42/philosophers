/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:50:08 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 22:52:23 by ka-tan           ###   ########.fr       */
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

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;
struct s_table // whole restaurant; stores info that philos need to know
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	int				stop;

	long			start_time;
	pthread_t		monitor_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philo;
};

struct s_philo // stores things specific to 1 philos
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;

	pthread_t		thread;
	pthread_mutex_t	meal_mutex;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_table			*table;
};

//actions.c
void	take_fork(t_philo *philo);
void	put_forks(t_philo *philo);
void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo, long slp_duration);
void	do_think(t_philo *philo);

//cleanup.c
void	destroying_forks(t_table *table, int i);
void	destroying_philo_mutexes(t_table *table, int i);
void	cleanup(t_table *table);

int		ft_atoi(const char *str);

//init.c
int		init_forks(t_table *table);
int		init_table(t_table *table, char **argv);
int		init_philos(t_table *table);

//main.c
void	print_instructions(void);
int		check_args(char **argv);

//monitor.c
void	set_stop_flag(t_table *table);
int		shld_stop(t_table *table);
void	*monitor_loop(void *arg);

//threads.c
int		creating_threads(t_table *table);
int		joining_threads(t_table *table);
void	*routine(void *arg);

//utils.c
int		ft_isdigit(int c);
int		is_positive_number(char *str);
void	print_state(t_philo *philo, char *str);
long	get_time_ms(void);

#endif
