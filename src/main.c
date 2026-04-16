/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:50:42 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/16 15:42:00 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
// #include <unistd.h>
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <stddef.h>
// #include <sys/time.h>
// #include <pthread.h>


void	print_instructions(void)
{
	printf("Usage should be:\n");
	printf("<no._of_philo> <time_to_die> <time_to_eat> <time_to_sleep>"); 
	printf("<[optional]number_of_times_each_philosopher_must_eat>\n");
}

int	check_args(t_table *table, int argc, char **argv)
{
	if (!ft_is_digit(ft_atoi(argv[1])))
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	if (!ft_is_digit(ft_atoi(argv[2])) || !ft_is_digit(ft_atoi(argv[3])) || !ft_is_digit(ft_atoi(argv[4])))
	{
		printf("Error: Invalid time\n");
		return (1);
	}
	if (argv[5])
	{
		if (!!ft_is_digit(ft_atoi(argv[5])))
			printf("Error: Invalid number to times each philosopher must eat\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo philo;

	if (argc < 5 || argc > 6)
		return (print_instructions(), 1);
	init_table(&table);
	if (!check_args(&data, argc, argv))
		return (print_instructions(), 1);
	if (!init_mlx(&data))
	{
		ft_printf("Error\n");
		return (1);
	}
	setup_hooks(&data);
	render_fractal(&data);
	mlx_loop(data.mlx);
	return (0);
}

/* 
void	*print_instructions(void *arg)
{
	(void)arg;
	printf("Usage should be:\n");
	printf("<no._of_philo> <time_to_die> <time_to_eat> <time_to_sleep> ");
	printf("<[optional]number_of_times_each_philosopher_must_eat>\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t t1, t2;

	(void)argc;
	(void)argv;
	if (pthread_create(&t1,NULL, &print_instructions, NULL) != NULL)
		return (1);
	pthread_create(&t2,NULL, &print_instructions, NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return(0);

} */
