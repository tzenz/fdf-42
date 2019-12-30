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

void		isometric(float *x, float *y, float z)
{
	float 	pre_x;
	float 	pre_y;

	if (z)
		z = 2;
	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * (float)cos(0.523599);
	*y = -z + (pre_x + pre_y) * (float)sin(0.523599);
//	printf("cos - %f sin - %f\n", cos(0.523599), sin(0.523599));
}

void		rotateimage(float *x, float *y, float *z)
{
	float	pre_x;
	float	pre_y;

	pre_x = *x;
	pre_y = *y;
	*y = pre_y * (float)cos(0.523599) + *z * (float)sin(0.523599);
	*z = -pre_y * (float)sin(0.523599) + *z * (float)cos(0.523599);
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
	isometric(&x, &y, (float)z);
	isometric(&x1, &y1, (float)z1);

//	if (st->x || st->y)
//	{
//		rotateimage(&x, &y, &z);
//		rotateimage(&x1, &y1, &z);
//
//		ft_putchar('\n');
//		ft_putnbr((int)st->x);
//		ft_putchar('\n');
//		ft_putnbr((int)st->y);
//		ft_putchar('\n');
//
//	}

	st->i = (x * 4 + 4 * WIN_WIDTH * y) * 5;
	st->j = (x1 * 4 + 4 * WIN_WIDTH * y1) * 5;

	if (st->x || st->y)
	{
		st->i += 8400;
		st->j += 8400;
	}

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
	while ((int)(x + y) < (int)st->j)
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
	ft_putstr("  sss   \n");
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
