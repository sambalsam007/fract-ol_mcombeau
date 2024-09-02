/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:19:51 by mcombeau          #+#    #+#             */
/*   Updated: 2024/09/02 14:14:27 by samd-hoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* type_cmp:
*	Parses the given fractal type argument and checks against
*	the name (i.e. "mandelbrot"), the associated letter (i.e. "M")
*	and the associated number (i.e. "1").
*	Returns true if the argument matches one of these requirements,
*	false if not.
*/
static int	type_cmp(char *av, char *str, char c, char n)
{
	int	i;

	i = 0;
	while (av[i])
	{
		av[i] = ft_tolower(av[i]);
		i++;
	}
	if (!ft_strncmp(av, str, ft_strlen(str) + 1))
		return (1);
	else if (av[1] == '\0' && (av[0] == c || av[0] == n))
		return (1);
	return (0);
}

/* get_set:
*	Retrieves the set specified in program arguments.
*	If no valid set was provided, it displays a help
*	message and quits the program.
*/
static void	get_set(t_fractol *f, char **av)
{
	if (type_cmp(av[1], "mandelbrot", 'm', '1'))
		f->set = MANDELBROT;
	else if (type_cmp(av[1], "julia", 'j', '2'))
		f->set = JULIA;
	else if (type_cmp(av[1], "burning ship", 'b', '3'))
		f->set = BURNING_SHIP;
	else if (type_cmp(av[1], "tricorn", 't', '4'))
		f->set = TRICORN;
	else if (type_cmp(av[1], "mandelbox", 'x', '5'))
		f->set = MANDELBOX;
	else
		help_msg(f);
}

/* get_julia_starting_values:
*	Checks whether starting values were provided at program launch
*	for the Julia set. If not, default Julia values are assigned.
*	If values were provided, parses them, returning an error message
*	if the values are not valid.
*/
static void	get_julia_starting_values(t_fractol *f, int ac, char **av)
{
	if (f->set != JULIA || ac == 2)
	{
		f->kr = -0.766667;
		f->ki = -0.090000;
		return ;
	}
	if (ac == 3)
		help_msg(f);
	if (!ft_strchr(av[2], '.'))
		help_msg(f);
	if (!ft_strchr(av[3], '.'))
		help_msg(f);
	f->kr = ft_atof(av[2]);
	f->ki = ft_atof(av[3]);
	if (f->kr > 2.0 || f->kr < -2.0)
		help_msg(f);
	if (f->ki >= 2.0 || f->ki <= -2.0)
		help_msg(f);
}

/* handle_args:
*	Retrieves the set, the julia starting values and the color from
*	the arguments passed at program launch.
*/
static void	handle_args(t_fractol *f, int ac, char **av)
{
	get_set(f, av);
	if (f->set != JULIA && ac > 3)
		help_msg(f);
	else if (f->set == JULIA && ac > 5)
		help_msg(f);
	get_julia_starting_values(f, ac, av);
	get_color(f, ac, av);
}

/* main:
*	Initializes the fractol data structure, prints the program controls,
*	opens a new window and registers hooks to detect user interactions.
*	Loops infinitely until the user quits the process.
*/
void	s_breakpoint(void)
{
		printf("\n--break--\n");
		getchar();
}

int	main(int ac, char **av)
{
	t_fractol	f;

	if (ac < 2)
		help_msg(&f); 
	/*
	1. prints message
	2. clean exit
		depending on the state of typedef struct 'f'
		free this, close this, etc, ...
		-> to ensure a CLEAN exit
	*/
	clean_init(&f);
	printf("clean_init results:\n");
	printf("min_r\t%f\n",f.kr);
	/* Initiliazes t_fractol f
	 * with '0' values
	 * or NULL values.
	 */
	handle_args(&f, ac, av);
	printf("\nhandle_args results:\n");
	printf("min_r\t%f\n",f.kr);
	/* check if user wants mandelbrot or julia, burning ship, ...
	 * get julia starting values
	 */
	init(&f); 
	/*
	1. opens window
	2. set some (?) default values in the t_fractol structure
	*/
	render(&f); 
	/*
	1. check each pixel
		turn pixel into complex number
		check if number = part of fractal set
	2. construct image
	*/
	print_controls(); 
	/*
	1. print controls
	*/
	mlx_hook(f.win, EVENT_CLOSE_BTN, 0, end_fractol, &f);
	/*
		? make escape key, cross functional?
	*/
	mlx_key_hook(f.win, key_event, &f);
	/*
		? make keys functional
	*/
	mlx_mouse_hook(f.win, mouse_event, &f);
	/*
		? make mouse functional
	*/
	mlx_loop(f.mlx);
	/*
		? keep window open & functional
	*/
	// s_breakpoint();
}
