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
# define WIN_WIDTH 800
# define WIN_HIGHT 600


typedef struct		s_file
{
	int 			**s;
	int				width;
	int				hight;
	float 			zoom;
	int 			color;
	int 			swift_x;
	int 			swift_y;

	void			*mlx;
	void			*win;
	void			*img_ptr;
	int 			*img_data;

	float 			i;
	float 			j;
	float 			x;
	float			y;
}					file;

//void		drawimage(int x, int y, int x1, int y1, file *st);
//void		draw(file *st);
//void		isometric(int *x, int *y, int z);

void		rotateimage(float *x, float *y, float *z);
void		drawimage(float x, float y, float x1, float y1, file *st);
void		draw(file *st);
void		isometric(float *x, float *y, float z);

int 		drawline(float x, float y, float x1, float y1, file *st);
void		s_hight(file *st, char **argv);
void		ft_putsnbr(file *st);
int 		deal_key(int key, file *st);
void		drawp(file *st);

#endif