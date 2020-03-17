/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawimg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 11:24:57 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/01 17:09:34 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		drawline(t_file *st, t_cur *cur)
{
	int		signx;
	int		signy;
	int		error[2];

	cur->deltax = MOD(cur->x1 - cur->x);
	cur->deltay = MOD(cur->y1 - cur->y);
	signx = cur->x < cur->x1 ? 1 : -1;
	signy = cur->y < cur->y1 ? 1 : -1;
	error[0] = cur->deltax - cur->deltay;
	while (cur->x != cur->x1 || cur->y != cur->y1)
	{
		put_pix(st, cur);
		error[1] = error[0] * 2;
		if (error[1] > -cur->deltay)
		{
			error[0] -= cur->deltay;
			cur->x += signx;
		}
		if (error[1] < cur->deltax)
		{
			error[0] += cur->deltax;
			cur->y += signy;
		}
	}
	put_pix(st, cur);
}

void		rotate(t_cur *cur, t_file *st)
{
	rotate_x(&cur->y, &cur->z, st->k->angle_x);
	rotate_x(&cur->y1, &cur->z1, st->k->angle_x);
	rotate_y(&cur->x, &cur->z, st->k->angle_y);
	rotate_y(&cur->x1, &cur->z1, st->k->angle_y);
	rotate_z(&cur->x, &cur->y, st->k->angle_z);
	rotate_z(&cur->x1, &cur->y1, st->k->angle_z);
	if (st->iso == 1)
	{
		isometric(&cur->x, &cur->y, cur->z);
		isometric(&cur->x1, &cur->y1, cur->z1);
	}
	cur->x += (((WIDTH - MENU_W) / 2) + MENU_W) + st->k->mx;
	cur->x1 += (((WIDTH - MENU_W) / 2) + MENU_W) + st->k->mx;
	cur->y += ((HIGHT + st->zoom * 10) / 2) + st->k->my;
	cur->y1 += ((HIGHT + st->zoom * 10) / 2) + st->k->my;
	st->color_start_x = cur->x;
	st->color_start_y = cur->y;
	drawline(st, cur);
	free(cur);
	cur = NULL;
}

t_cur		*color_zoom(t_cur *cur, t_file *st)
{
	cur->z = st->s[cur->y][cur->x];
	cur->z1 = st->s[cur->y1][cur->x1];
	cur->color_z = cur->z;
	cur->color_z1 = cur->z1;
	cur->x *= st->zoom;
	cur->y *= st->zoom;
	cur->z *= st->zoom;
	cur->x1 *= st->zoom;
	cur->y1 *= st->zoom;
	cur->z1 *= st->zoom;
	cur->z *= st->ziso;
	cur->z1 *= st->ziso;
	cur->x -= (st->zoom * st->width) / 2;
	cur->x1 -= (st->zoom * st->width) / 2;
	cur->y -= (st->zoom * st->hight) / 2;
	cur->y1 -= (st->zoom * st->hight) / 2;
	return (cur);
}

t_cur		*newcur(int x, int y, int x1, int y1)
{
	t_cur	*cur;

	cur = (t_cur *)ft_memalloc(sizeof(t_cur));
	cur->x = x;
	cur->y = y;
	cur->x1 = x1;
	cur->y1 = y1;
	return (cur);
}

void		draw(t_file *st, int x, int y)
{
	while (y < st->hight)
	{
		x = 0;
		while (x < st->width)
		{
			if (x < st->width - 1)
				rotate(color_zoom(newcur(x, y, x + 1, y), st), st);
			if (y < st->hight - 1)
				rotate(color_zoom(newcur(x, y, x, y + 1), st), st);
			x++;
		}
		y++;
	}
}
