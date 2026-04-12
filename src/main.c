/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:50:42 by ka-tan            #+#    #+#             */
/*   Updated: 2026/04/11 19:14:06 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_instructions(void)
{
	printf("Usage should be:\n");
	printf("<no._of_philo> <time_to_die> <time_to_eat> <time_to_sleep>"); 
	printf("<[optional]number_of_times_each_philosopher_must_eat>\n");
}

// checks if is mandelbrot or julia, whether parameters keyed in is correct
int	parse_args(t_data *data, int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "mandelbrot", 11) && argc == 2)
	{
		data->fractol_type = MANDELBROT;
		return (1);
	}
	if (!ft_strncmp(argv[1], "julia", 6) && argc == 4)
	{
		if (!is_valid_double(argv[2]) || !is_valid_double(argv[3]))
			return (ft_printf("Error: Parameters must be valid numbers\n"), 0);
		data->fractol_type = JULIA;
		data->c.real = ft_atof(argv[2]);
		data->c.imag = ft_atof(argv[3]);
		if (fabs(data->c.real) > 2 || fabs(data->c.imag) > 2)
			return (ft_printf("Error: Parameters must be between -2 & 2\n"), 0);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2 || argc > 7)
		return (print_instructions(), 1);
	init_default_values(&data);
	if (!parse_args(&data, argc, argv))
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
