/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawimg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 11:24:57 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/30 11:24:58 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		isometric(float *x, float *y, file *st, float z)
{
	float 	pre_x;
	float 	pre_y;

	if (z)
		z = st->ziso;
	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * (float)cos(0.523599);
	*y = -z + (pre_x + pre_y) * (float)sin(0.523599);
}

void		drawimage(float x, float y, float x1, float y1, file *st)
{
	int 	count;
	int 	*b1;
	float 	z;
	float 	z1;
	float 	max;
	float 	x_step;
	float	y_step;
	float 	wcount;

	z = st->s[(int)y][(int)x];
	z1 = st->s[(int)y1][(int)x1];
	st->color = (z || z1) ? 0xF2F2F2 : 0x447B87;
	b1 = st->img_data;

//	st->i = (99000 * 3) * 3;
//	st->j = (99000 * 3) * 3;

	x += st->zoom - st->zoom;
	y += st->zoom - st->zoom;
	x1 += st->zoom - st->zoom;
	y1 += st->zoom - st->zoom;

//	rotate(&x, &y, st);
//	rotate(&x1, &y1, st);
//	rotate_x(&y, &z, st);
//	rotate_x(&y1, &z1, st);
//	rotate_y(&x, &z, st);
//	rotate_y(&x1, &z1, st);
//	rotate_z(&y, &z, st);
//	rotate_z(&y1, &z1, st);

	isometric(&x, &y, st, (float)z);
	isometric(&x1, &y1, st, (float)z1);
	printf("x - %f y - %f x1 - %f y1 - %f\n", x, y, x1, y1);
	if (x < 0 || y < 0 || x1 < 0 || y1 < 0)
		return;
	st->i = ((x * 4 + 4 * WIN_WIDTH * y) * st->zoom);
	st->j = ((x1 * 4 + 4 * WIN_WIDTH * y1) * st->zoom);

//	printf("i - %f j - %f\n", st->i, st->j);
	count = 1;
	wcount = 0;

	x = (int)st->i % WIN_WIDTH;
	y = (int)st->i / WIN_WIDTH;
	x1 = (int)st->j % WIN_WIDTH;
	y1 = (int)st->j / WIN_WIDTH;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	y = (y > 0) ? y * WIN_WIDTH : y;

	while ((int)(x + y) < (int)st->j && x + y < MAXPIX)
	{
		b1[(int)(x + y)] = st->color;
		x += x_step;
		if ((int)(wcount += y_step) == count)
		{
			y += WIN_WIDTH;
			count += 1;
		}
	}
}

void		draw(file *st)
{
	float 	x;
	float 	y;

	y = 0;
	while (y < (float)st->hight)
//	while (y < (float)st->hight && y < 1)
	{
		x = 0;
		while (x <(float) st->width)
//		while (x < (float)st->width && x < 1)
		{
			if (x < (float)st->width - 1)
			{
				drawimage(x, y, x + 1, y, st);
			}
			if (y < (float)st->hight - 1)
			{
				drawimage(x, y, x, y + 1, st);
			}
			x++;
		}
		y++;
	}
}
