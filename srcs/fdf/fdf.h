/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:53:18 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/24 11:53:20 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"
# include "../minilibx_macos/mlx.h"
# include <stdio.h>
# include "math.h"
# include "color.h"

# define MOD(a) ((a > 0) ? a : -a)
# define MAX(a,b) ((a > b) ? a : b)

typedef struct		s_key
{
	double			angle_x;
	double 			angle_y;
	double 			angle_z;
	float 			mx;
	float 			my;
}					t_key;

typedef struct 		s_cur
{
	int 			color_z;
	int 			color_z1;
	float			x_step;
	float 			y_step;
	float			wcount;
	int				count;
	float			max;
	int 			maxz;
	int 			minz;

	float			x;
	float 			y;
	float 			x1;
	float			y1;
	float 			z;
	float 			z1;
}					t_cur;

typedef struct		s_file
{
	int 			**s;
	int				width;
	int				hight;
	float 			zoom;

	void			*mlx;
	void			*win;
	void			*img_ptr;
	int 			*img_data;

	float			x;
	float			y;
	float 			i;
	float 			j;
	float 			ziso;
	int 			button;
	float 			W_W;
	float 			W_H;
	int 			X_IMG;
	int 			Y_IMG;

	t_cur 			*Scur;
	t_key			*Skey;
}					t_file;

typedef struct		s_point
{
	float 			x;
	float 			y;
	float 			x1;
	float 			y1;
}					t_point;

int 		maxz(t_file *st);
int 		minz(t_file *st);
int			color_pix(t_cur *cur, t_file *st);
void		background(t_file *st);

//void		draw(file *st);
//void		isometric(int *x, int *y, int z);

void		rotate(t_file *st, t_point *pt, t_cur *cur);
void		rotate_x(float *y, float *z, t_file *st);
void		rotate_z(float *x, float *y, t_file *st);
void		rotate_y(float *x, float *z, t_file *st);

int 		mouse_press(int button, int x, int y, t_file *st);
void		putclean(t_file *st, int key, int button);
void		drawimage(t_point *pt, t_file *st);

void		draw(t_file *st, float x, float y);
void		isometric(float *x, float *y, t_file *st, float z);

void		s_hight(t_file *st, char **argv);

#endif