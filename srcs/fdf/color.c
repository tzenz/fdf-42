/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:53:10 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 15:53:44 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			cur_color(double z, t_file *st)
{
	double	prec;

	z = (st->minz) ? z += MOD(st->minz) : z;
	prec = (z / st->maxz) * 100;
	if (prec >= 20 && prec <= 40)
		return (COLOR_2);
	else if (prec >= 40 && prec <= 60)
		return (COLOR_3);
	else if (prec >= 60 && prec <= 80)
		return (COLOR_4);
	else if (prec >= 80 && prec <= 100)
		return (COLOR_5);
	return (COLOR_1);
}

int			color_pix(t_cur *cur, t_file *st)
{
	int		blue;
	int		green;
	int		red;
	double	prec;

	if (cur->deltax > cur->deltay)
		prec = precent(cur->x, cur->x1, st->color_start_x);
	else
		prec = precent(cur->y, cur->y1, st->color_start_y);
	red = get_light((cur_color(cur->color_z, st) >> 16) & 0xFF,
			(cur_color(cur->color_z1, st) >> 16) & 0xFF, prec);
	blue = get_light((cur_color(cur->color_z, st) >> 8) & 0xFF,
			(cur_color(cur->color_z1, st) >> 8) & 0xFF, prec);
	green = get_light(cur_color(cur->color_z, st) & 0xFF,
			cur_color(cur->color_z1, st) & 0xFF, prec);
	return ((red << 16) | (blue << 8) | green);
}

int			maxz(t_file *st)
{
	int		max;
	int		i;
	int		j;

	i = 0;
	max = 0;
	while (i < st->hight)
	{
		j = 0;
		while (j < st->width)
		{
			if (st->s[i][j] > max)
				max = st->s[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int			minz(t_file *st)
{
	int		min;
	int		i;
	int		j;

	i = 0;
	min = 0;
	while (i < st->hight)
	{
		j = 0;
		while (j < st->width)
		{
			if (st->s[i][j] < min)
				min = st->s[i][j];
			j++;
		}
		i++;
	}
	return (min);
}
