/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:53:18 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 16:24:36 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "math.h"
# include "color.h"

# define MOD(a) (((a) > 0) ? (a) : -(a))
# define MIN(a,b) ((a < b) ? a : b)
# define WIDTH 1920
# define HIGHT 1080
# define MENU_W 250

typedef struct		s_window
{
	void			*mlx;
	void			*win;
	void			*i_p;
	int				*i_d;
}					t_window;

typedef struct		s_key
{
	double			angle_x;
	double			angle_y;
	double			angle_z;
	int				mx;
	int				my;
}					t_key;

typedef struct		s_mouse
{
	int				x;
	int				y;
	int				prev_x;
	int				prev_y;
	int				pressed;

}					t_mouse;

typedef struct		s_cur
{
	int				color_z;
	int				color_z1;

	int				deltax;
	int				deltay;

	int				x;
	int				y;
	int				x1;
	int				y1;
	int				z;
	int				z1;

}					t_cur;

typedef struct		s_file
{
	int				**s;
	int				width;
	int				hight;
	int				zoom;
	int				maxz;
	int				minz;

	int				color_start_x;
	int				color_start_y;
	int				ziso;

	t_key			*k;
	t_window		*w;
	t_mouse			*m;
}					t_file;

void				readfile(t_file *st, char **argv);
void				background(t_file *st);
void				put_pix(t_file *st, t_cur *cur);
double				precent(double current, double end, double start);
int					color_pix(t_cur *cur, t_file *st);
int					maxz(t_file *st);
int					minz(t_file *st);
void				isometric(int *x, int *y, int z);
void				rotate_x(int *y, int *z, double alpha);
void				rotate_y(int *x, int *z, double beta);
void				rotate_z(int *x, int *y, double gamma);
void				print_menu(t_file *st);
void				key_controls(t_file *st);
void				mouse_controls(t_file *st);
void				put_clean(t_file *st);
void				draw(t_file *st, int x, int y);
#endif
