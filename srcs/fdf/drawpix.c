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
	if (key == 126)
		st->swift_y -= 15;
	if (key == 125)
		st->swift_y += 15;
	if (key == 123)
		st->swift_x -= 15;
	if (key == 124)
		st->swift_x += 15;
	if (key == 69)
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
	x *= st->zoom;
	y *= st->zoom;
	x1 *= st->zoom;
	y1 *= st->zoom;
//---------------color----------
	st->color = (z || z1) ? 0x228B22 : 0xFFE4E1;
//----------------3D------------
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
//----------------shift---------
	x += (float)st->swift_x;
	y += (float)st->swift_y;
	x1 += (float)st->swift_x;
	y1 += (float)st->swift_y;

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