/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:18:56 by mcombeau          #+#    #+#             */
/*   Updated: 2022/04/16 18:07:07 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom(t_fractol *f, double zoom)
{
	double	center_r;
	double	center_i;

	center_r = f->min_r - f->max_r;
	center_i = f->max_i - f->min_i;
	f->max_r = f->max_r + (center_r - zoom * center_r) / 2;
	f->min_r = f->max_r + zoom * center_r;
	f->min_i = f->min_i + (center_i - zoom * center_i) / 2;
	f->max_i = f->min_i + zoom * center_i;
}

void	move(t_fractol *f, double distance, char direction)
{
	double	center_r;
	double	center_i;

	center_r = f->max_r - f->min_r;
	center_i = f->max_i - f->min_i;
//	printf("center r = %f, center_i = %f, distance to move = %f\n", center_r, center_i, distance);
	if (direction == 'R')
	{
//		printf("Before move right min_r = %f, max_r = %f\n", f->min_r, f->max_r);
		f->min_r += center_r * distance;
		f->max_r += center_r * distance;
//		printf("After move right min_r = %f, max_r = %f\n", f->min_r, f->max_r);
	}
	else if (direction == 'L')
	{
//		printf("Before move left min_r = %f, max_r = %f\n", f->min_r, f->max_r);
		f->min_r -= center_r * distance;
		f->max_r -= center_r * distance;
//		printf("Before move left min_r = %f, max_r = %f\n", f->min_r, f->max_r);
	}
	else if (direction == 'D')
	{
//		printf("Before move DOWN min_i = %f, max_i = %f\n", f->min_i, f->max_i);
		f->min_i -= center_i * distance;
		f->max_i -= center_i * distance;
//		printf("After move DOWN min_i = %f, max_i = %f\n", f->min_i, f->max_i);
	}
	else if (direction == 'U')
	{
//		printf("Before move UP min_r = %f, max_r = %f\n", f->min_r, f->max_r);
		f->min_i += center_i * distance;
		f->max_i += center_i * distance;
//		printf("Before move UP min_r = %f, max_r = %f\n", f->min_r, f->max_r);
	}
}

int	key_event_extend(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_SPACE)
		color_shift(mlx);
	else if (keycode == KEY_ONE && mlx->set != MANDELBROT)
	{
		mlx->set = MANDELBROT;
		get_orientation(mlx);
	}
	else if (keycode == KEY_TWO && mlx->set != JULIA)
	{
		mlx->set = JULIA;
		get_orientation(mlx);
	}
	else if (keycode == KEY_THREE && mlx->set != BURNING_SHIP)
	{
		mlx->set = BURNING_SHIP;
		get_orientation(mlx);
	}
	else if (keycode == KEY_FOUR && mlx->set != TRICORN)
	{
		mlx->set = TRICORN;
		get_orientation(mlx);
	}
	else
		return (1);
	render(mlx);
	return (0);
}

/*	char	*keycode_str;
	keycode_str = ft_itoa(keycode);
	ft_putendl_fd(keycode_str, 2);
	free(keycode_str);
	*/
int	key_event(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		end_fractol(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		zoom(mlx, 2);
	else if (keycode == KEY_UP || keycode == KEY_W)
		move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN || keycode == KEY_S)
		move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT || keycode == KEY_A)
		move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
		move(mlx, 0.2, 'R');
	else if (!key_event_extend(keycode, mlx))
		return (1);
	else
		return (1);
	render(mlx);
	return (0);
}

/*	char *keycode_str;
	keycode_str = ft_itoa(keycode);
	ft_putendl_fd(keycode_str, 2);
	free(keycode_str);
*/
int	mouse_event(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_WHEEL_UP)
	{
		zoom(mlx, 0.5);
		x -= WIDTH / 2;
		y -= HEIGHT / 2;
		if (x < 0)
			move(mlx, (double)x * -1 / WIDTH, 'L');
		else if (x > 0)
			move(mlx, (double)x / WIDTH, 'R');
		if (y < 0)
			move(mlx, (double)y * -1 / HEIGHT, 'U');
		else if (y > 0)
			move (mlx, (double)y / HEIGHT, 'D');
	}
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom(mlx, 2);
	else if (keycode == MOUSE_BTN)
	{
		if (mlx->set == JULIA)
			julia_shift(x, y, mlx);
	}
	else
		return (0);
	render(mlx);
	return (0);
}