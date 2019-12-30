/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 15:57:30 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/24 15:57:32 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 		deal_key(int key, file *st)
{
	if (key == 53)
		exit(0);
		st->zoom += 1;
	if (key == 78)
		st->zoom -= 1;
	mlx_clear_window(st->mlx, st->win);
	draw(st);
	return (0);
}


int 		drawline(float x, float y, float x1, float y1, file *st)
{
	float	x_step;
	float	y_step;
	float 	max;
	int 	z;
	int 	z1;

	int 	i;
	int 	j;

	z = st->s[(int)y][(int)x];
	z1 = st->s[(int)y1][(int)x1];
//---------------zoom-----------
	x *= 20;
	y *= 20;
	x1 *= 20;
	y1 *= 20;
//---------------color----------
	st->color = (z || z1) ? 0x228B22 : 0xFFE4E1;
//----------------3D------------
	isometric(&x, &y, st, (float)z);
	isometric(&x1, &y1, st, (float)z1);
//----------------shift---------
	x += 300;
	y += 100;
	x1 += 300;
	y1 += 100;

	printf("x - %f y - %f\n x1 - %f y1 - %f\n\n", x, y, x1, y1);

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;

	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(st->mlx, st->win, x, y, st->color);
		x += x_step;
		y += y_step;
	}
	return (0);
}

void		drawp(file *st)
{
	float		x;
	float		y;

	y = 0;
	while (y < st->hight)
	{
		x = 0;
		while (x < st->width)
		{
			if (x < st->width - 1)
				drawline(x, y, x + 1, y, st);
			if (y < st->hight - 1)
				drawline(x, y, x, y + 1, st);
			x++;
		}
		y++;
	}
}