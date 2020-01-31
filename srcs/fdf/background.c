/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:23:28 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 15:52:04 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		background(t_file *st)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x + y < WIDTH * HIGHT)
	{
		x = 0;
		while (x <= MENU_W)
			st->w->i_d[x++ + y] = BACK_MENU;
		while (x < WIDTH)
			st->w->i_d[x++ + y] = BACKGROUND;
		y += WIDTH;
	}
}

void		put_pix(t_file *st, t_cur *cur)
{
	int		color;
	int		i;

	if (cur->x > MENU_W && cur->x < WIDTH && cur->y >= 0 && cur->y < HIGHT)
	{
		i = cur->x + (cur->y * WIDTH);
		color = color_pix(cur, st);
		if (st->w->i_d[i] == COLOR_5 ||
			(st->w->i_d[i] != BACKGROUND && color == COLOR_1))
			return ;
		st->w->i_d[i] = color;
	}
}

double		precent(double current, double end, double start)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (MOD(placement) / MOD(distance)));
}
