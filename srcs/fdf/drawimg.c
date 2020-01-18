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

void		draw(t_file *st, float x, float y)
{
	t_point *pt;

	pt = (t_point *)ft_memalloc(sizeof(t_point));
	while (pt->y < (float)st->hight)
//	while (pt->y < (float)st->hight && pt->y < 1)
	{
		pt->x = 0;
		pt->x1 = 0;
		while (pt->x <(float) st->width)
//		while (pt->x < (float)st->width && pt->x < 10)
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
	free(pt);
}

void		color(t_file *st, t_cur *cur, t_point *pt)
{
	cur->x = pt->x;
	cur->y = pt->y;
	cur->x1 = pt->x1;
	cur->y1 = pt ->y1;
	cur->count = 1;
	cur->z = (float)st->s[(int) pt->y][(int) pt->x];
	cur->z1 = (float)st->s[(int) pt->y1][(int) pt->x1];
	cur->color_z = (int)cur->z;
	cur->color_z1 = (int)cur->z1;
}

void		rotate(t_file *st, t_point *pt, t_cur * cur)
{
	isometric(&cur->x, &cur->y, st, cur->z);
	isometric(&cur->x1, &cur->y1, st, cur->z1);
//	rotate_x(&cur->y, &cur->z, st);
//	rotate_x(&cur->y1, &cur->z1, st);
	rotate_y(&cur->x, &cur->z, st);
	rotate_y(&cur->x1, &cur->z1, st);
}

void		zoom(t_file *st, t_cur *cur, t_point *pt)
{
	st->i = (cur->x * 4 + 4 * st->W_W * cur->y);
	st->j = (cur->x1 * 4 + 4 * st->W_W * cur->y1);
	st->i *= st->zoom;
	st->j *= st->zoom;
	st->i += ((((st->W_H / 2) + st->Skey->my) - ((st->zoom + st->zoom) * 2)) * st->W_W) // суперстрока - move, сдвиг во время zoom
			+ (st->W_W / 2 + st->Skey->mx) - (st->zoom * 15);
	st->j += ((((st->W_H / 2) + st->Skey->my) - ((st->zoom + st->zoom) * 2)) * st->W_W)
			+ (st->W_W / 2 + st->Skey->mx) - (st->zoom * 15);
	cur->x = (float)((int) st->i % (int)st->W_W);
	cur->y = (float)((int) st->i / (int)st->W_W);
	cur->x1 = (float)((int) st->j % (int)st->W_W);
	cur->y1 = (float)((int) st->j / (int)st->W_W);
	cur->x_step = cur->x1 - cur->x;
	cur->y_step = cur->y1 - cur->y;
	cur->max = MAX(MOD(cur->x_step), MOD(cur->y_step));
	cur->x_step /= cur->max;
	cur->y_step /= cur->max;
	cur->y = (cur->y >= 0) ? cur->y * st->W_W : cur->y;
	cur->y1 = (cur->y1 >= 0) ? cur->y1 * st->W_W : cur->y1;
}

void		drawline(t_file *st, t_cur *cur, t_point *pt)
{
	if ((int)(cur->x + cur->y) < (int)(cur->x1 + cur->y1))
		while ((int) (cur->x + cur->y) < (int) (cur->x1 + cur->y1)
					&& cur->x + cur->y < st->W_W * st->W_H)
		{
			st->img_data[(int) (cur->x + cur->y)] = color_pix(cur, st);
			cur->x += cur->x_step;
			if ((int) (cur->wcount += cur->y_step) == cur->count)
			{
				cur->y += st->W_W;
				cur->count += 1;
			}
		}
	else if ((int)(cur->x + cur->y) + 1 > (int)(cur->x1 + cur->y1))
		while ((int) (cur->x + cur->y) > (int) (cur->x1 + cur->y1)
					&& cur->x + cur->y < st->W_W * st->W_H)
		{
			st->img_data[(int) (cur->x + cur->y)] = color_pix(cur, st);
			cur->x -= (cur->x_step < 0) ? MOD(cur->x_step) : -cur->x_step;
			if ((int) (cur->wcount += MOD(cur->y_step)) == cur->count)
			{
				cur->y -= st->W_W;
				cur->count += 1;
			}
		}
}

void		drawimage(t_point *pt, t_file *st)
{
	t_cur	*cur;

	cur = (t_cur *)ft_memalloc(sizeof(t_cur));
	color(st, cur, pt);
	rotate(st, pt, cur);
	zoom(st, cur, pt);
	drawline(st, cur, pt);
	free(cur);
}
