/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:50:42 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/09 22:45:23 by ka-tan           ###   ########.fr       */
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
	printf(" <[optional]number_of_times_each_philosopher_must_eat>\n");
}

int	check_args(char **argv)
{
	if (!is_positive_number(argv[1]))
	{
		printf("Error: Invalid number of philosophers\n");
		return (1);
	}
	if (!is_positive_number(argv[2]) || !is_positive_number(argv[3]) || !is_positive_number(argv[4]))
	{
		printf("Error: Invalid time\n");
		return (1);
	}
	if (argv[5] && !is_positive_number(argv[5]))
	{
		printf("Error: Invalid number to times each philosopher must eat\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (print_instructions(), 1);
	if (check_args(argv))
		return (print_instructions(), 1);
	if (init_table(&table, argv))
		return (printf("Error\n"), 1);
	if (init_philos(&table))
		return (cleanup(&table), 1);
	if (creating_threads(&table))
		return (cleanup(&table), 1);
	if (joining_threads(&table))
		return (cleanup(&table), 1);
	cleanup(&table);
	return (0);
}
