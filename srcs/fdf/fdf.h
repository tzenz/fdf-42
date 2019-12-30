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
# define WIN_WIDTH 2000
# define WIN_HIGHT 1200


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

	float 			i;
	float 			j;
	double			x;
	double			y;
	float 			ziso;
	int 			button;
}					file;

//void		drawimage(int x, int y, int x1, int y1, file *st);
//void		draw(file *st);
//void		isometric(int *x, int *y, int z);

void		rotate_x(float *y, float *z, file *st);
void		rotate_z(float *x, float *y, file *st);
void		rotate_y(float *x, float *z, file *st);

int 		mouse_press(int button, int x, int y, file *st);
void		putclean(file *st);
void		drawimage(float x, float y, float x1, float y1, file *st);
void		draw(file *st);
void		isometric(float *x, float *y, file *st, float z);

int 		drawline(float x, float y, float x1, float y1, file *st);
void		s_hight(file *st, char **argv);
void		ft_putsnbr(file *st);
int 		deal_key(int key, file *st);
void		drawp(file *st);

#endif