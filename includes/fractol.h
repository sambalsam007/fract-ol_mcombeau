#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <math.h>

/*  Dimensions    */
# define WIDTH 900
# define HEIGHT 900
# define MAX_ITERATIONS 80

/*  Fractal sets    */
# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3
# define TRICORN 4

/*  Keycodes    */
# define EVENT_CLOSE_BTN 17
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_SPACE 32
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 3
# define MOUSE_BTN 1
# define MOUSE_BTN_2 3

typedef struct  s_fractol
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *buf;
    int     set;
    double  min_r;
    double  max_r;
    double  min_i;
    double  max_i;
    double  cr;
    double  ci;
    int     *color_scheme;
}   t_fractol;

/*  Functions   */
int mandelbrot(t_fractol *f, double cr, double ci, int x, int y);
int julia(t_fractol *f, double zr, double zi, double cr, double ci, int x, int y);
int burning_ship(t_fractol *f, double cr, double ci, int x, int y);
int tricorn(t_fractol *f, double cr, double ci, int x, int y);

/*  Draw    */
void    render(t_fractol *f);
void    set_colors(t_fractol *f, int r, int g, int b);

/*  Events   */
int key_event(int keycode, t_fractol *mlx);
int mouse_event(int keycode, int x, int y, t_fractol *mlx);

/*  Utils   */
int    end_fractol(t_fractol *mlx);
void    exit_error(int error_code);
int     msg(char *str1, char *str2, int errno);
void help_msg(void);

#endif