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

//void		draw(file *st)
//{
//	float 	x;
//	float 	y;
//
//	y = 0;
//	x = 0;
//	while (y < (float)st->hight)
////	while (y < (float)st->hight && y < 1)
//	{
//		x = 0;
//		while (x <(float) st->width)
////		while (x < (float)st->width && x < 1)
//		{
////			if (x < (float)st->width - 1)
////				drawimage(x, y, x + 1, y, st);
////			if (y < (float)st->hight - 1)
////				drawimage(x, y, x, y + 1, st);
//			x++;
//		}
//		y++;
//	}
//	printf("x - %f y - %f\n", x, y);
//}

void		draw(file *st)
{
	t_point *pt;

	pt = (t_point *)ft_memalloc(sizeof(t_point));
	while (pt->y < (float)st->hight)
	{
		pt->x = 0;
		pt->x1 = 0;
		while (pt->x <(float) st->width)
		{
			if (pt->x < (float)st->width - 1)
			{
				pt->x1++;
				drawimage(pt, st);
				pt->x1--;
			}
			if (pt->y < (float)st->hight - 1)
			{
				pt->y1++;
				drawimage(pt, st);
				pt->y1--;
			}
			pt->x++;
			pt->x1++;
		}
		pt->y++;
		pt->y1++;
	}
}

void		color(t_point *pt, file *st)
{
	pt->z = (float)st->s[(int) pt->y][(int) pt->x];
	pt->z1 = (float)st->s[(int) pt->y1][(int) pt->x1];
	st->color = (pt->z || pt->z1) ? 0x01a74e : 0xed6321;
}

//void		zoom()

void		drawimage(t_point *pt, file *st)
{
	float x_step;
	float y_step;
	float wcount;
	int count;
	float max;

	float 	x;
	float	y;
	float 	x1;
	float	y1;

	x = pt->x;
	y = pt->y;
	x1 = pt->x1;
	y1 = pt ->y1;

	count = 1;
	wcount = 0;
	color(pt, st);

//	rotate(&x, &y, st);
//	rotate(&x1, &y1, st);
//	rotate_x(&y, &z, st);
//	rotate_x(&y1, &z1, st);
//	rotate_y(&x, &z, st);
//	rotate_y(&x1, &z1, st);
//	rotate_z(&y, &z, st);
//	rotate_z(&y1, &z1, st);

	isometric(&x, &y, st, (float) pt->z);
	isometric(&x1, &y1, st, (float) pt->z1);

	st->i = (x * 4 + 4 * st->W_W * y);
	st->j = (x1 * 4 + 4 * st->W_W * y1);

	st->i *= st->zoom;
	st->j *= st->zoom;

	st->i += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
	st->j += ((st->W_H / 2) * st->W_W) + st->W_W / 2;

	x = (int) st->i % (int)st->W_W;
	y = (int) st->i / (int)st->W_W;
	x1 = (int) st->j % (int)st->W_W;
	y1 = (int) st->j / (int)st->W_W;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	y = (y >= 0) ? y * st->W_W : y;
	y1 = (y1 >= 0) ? y1 * st->W_W : y1;
	while ((int) (x + y) < (int) (x1 + y1) && x + y < st->W_W * st->W_H)
	{
		st->img_data[(int) (x + y)] = st->color;
		x += x_step;
		if ((int) (wcount += y_step) == count)
		{
			y += st->W_W;
			count += 1;
		}
	}
}

//void		drawimage(float x, float y, float x1, float y1, file *st)
//{
//	int count;
//	int *b1;
//	float z;
//	float z1;
//	float max;
//	float x_step;
//	float y_step;
//	float wcount;
//
//	count = 1;
//	wcount = 0;
//	z = st->s[(int) y][(int) x];
//	z1 = st->s[(int) y1][(int) x1];
//	st->color = (z || z1) ? 0x01a74e : 0xed6321;
//	b1 = st->img_data;
//
////	rotate(&x, &y, st);
////	rotate(&x1, &y1, st);
////	rotate_x(&y, &z, st);
////	rotate_x(&y1, &z1, st);
////	rotate_y(&x, &z, st);
////	rotate_y(&x1, &z1, st);
////	rotate_z(&y, &z, st);
////	rotate_z(&y1, &z1, st);
//
//	isometric(&x, &y, st, (float) z);
//	isometric(&x1, &y1, st, (float) z1);
//
//	st->i = (x * 4 + 4 * st->W_W * y);
//	st->j = (x1 * 4 + 4 * st->W_W * y1);
//
//	st->i *= st->zoom;
//	st->j *= st->zoom;
//
//	st->i += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
//	st->j += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
//
//	x = (int) st->i % (int)st->W_W;
//	y = (int) st->i / (int)st->W_W;
//	x1 = (int) st->j % (int)st->W_W;
//	y1 = (int) st->j / (int)st->W_W;
//
//	x_step = x1 - x;
//	y_step = y1 - y;
//	max = MAX(MOD(x_step), MOD(y_step));
//	x_step /= max;
//	y_step /= max;
//	y = (y >= 0) ? y * st->W_W : y;
//	y1 = (y1 >= 0) ? y1 * st->W_W : y1;
//	while ((int) (x + y) < (int) (x1 + y1) && x + y < st->W_W * st->W_H)
//	{
//		b1[(int) (x + y)] = st->color;
//		x += x_step;
//		if ((int) (wcount += y_step) == count)
//		{
//			y += st->W_W;
//			count += 1;
//		}
//	}
//}