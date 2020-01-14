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

# define MOD(a) ((a > 0) ? a : -a)
# define MAX(a,b) ((a > b) ? a : b)

typedef struct		s_file
{
	int 			**s;
	int				width;
	int				hight;
	float 			zoom;
	int 			color;
	double			angle_x;
	double 			angle_y;
	double 			angle_z;

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
}					file;

typedef struct		s_point
{
	float 			x;
	float 			y;
	float 			x1;
	float 			y1;
	float 			z;
	float 			z1;
}					t_point;

void		background(file *st);

//void		draw(file *st);
//void		isometric(int *x, int *y, int z);

void		rotate(float *x, float *y, file *st);
void		rotate_x(float *y, float *z, file *st);
void		rotate_z(float *x, float *y, file *st);
void		rotate_y(float *x, float *z, file *st);

int 		mouse_press(int button, int x, int y, file *st);
void		putclean(file *st, int key);
//void		drawimage(float x, float y, float x1, float y1, file *st);
void		drawimage(t_point *pt, file *st);

void		draw(file *st);
void		isometric(float *x, float *y, file *st, float z);

int 		drawline(float x, float y, float x1, float y1, file *st);
void		s_hight(file *st, char **argv);

#endif