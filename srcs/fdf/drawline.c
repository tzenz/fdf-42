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

#define MOD(a) ((a > 0) ? a : -a)

int 		drawline(float x, float y, float x1, float y1, file *st)
{
	float	x_step;
	float	y_step;
	float 	max;

	x *= st->zoom;
	y *= st->zoom;
	x1 *= st->zoom;
	y1 *= st->zoom;

	x_step = x1 - x;
	y_step = y1 - y;

	max = (MOD(x_step) > MOD(y_step)) ? x_step : y_step;
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(st->mlx, st->win, (int)x, (int)y, 0xffffff);
		x += x_step;
		y += y_step;
	}
	return (0);
}

void		draw(file *st)
{
	float	x;
	float	y;

	y = 0;
	while (y < (float)st->hight)
	{
		x = 0;
		while (x < (float)st->length)
		{
			drawline(x, y, x + 1, y, st);
			drawline(x, y, x, y + 1, st);
			x++;
		}
		y++;
	}
}