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
//		while (pt->x < (float)st->width && pt->x < 1)
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
	st->color = (cur->z || cur->z1) ? 0x01a74e : 0xed6321;
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
	st->i += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
	st->j += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
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

double 		precent(float start, float end, t_file *st)
{
	double	placement;
	double	distance;

	placement = start - (double)((int)st->i % (int)st->W_W);
	distance = end - (double)((int)st->i % (int)st->W_W);
//	printf("dist - %lg", distance);
	return ((distance == 0) ? 1.0 : (MOD(placement) / MOD(distance)));
}

int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			color_pix(t_cur *cur, t_file *st, int color_z0, int color_z10)
{
	int 	blue;
	int 	green;
	int 	red;
	double 	prec;

//	printf("prec - %lg\n", prec);
	if (cur->z == cur->z1 && cur->z > 0)
		return (color_z10);
	else if (cur->z == cur->z1 && cur->z == 0)
		return (color_z0);
	else
	{
//		if (cur->x > cur->x1)
			prec = precent(cur->x, cur->x1, st);
//		else
//			prec = precent(cur->y, cur->y1, st);
		red = get_light((color_z10 >> 16) & 0xFF, (color_z0 >> 16) & 0xFF, prec);
		blue = get_light((color_z10 >> 8) & 0xFF, (color_z0 >> 8) & 0xFF, prec);
		green = get_light(color_z10 & 0xFF, color_z0 & 0xFF, prec);
		return ((red << 16) | (blue << 8) | green);
	}

}

void		drawline(t_file *st, t_cur *cur, t_point *pt)
{
	if ((int)(cur->x + cur->y) < (int)(cur->x1 + cur->y1))
		while ((int) (cur->x + cur->y) < (int) (cur->x1 + cur->y1)
					&& cur->x + cur->y < st->W_W * st->W_H)
		{
			st->img_data[(int) (cur->x + cur->y)] = color_pix(cur, st, 0x3f51c7, 0x3fcdc7);
			cur->x += cur->x_step;
			if ((int) (cur->wcount += cur->y_step) == cur->count)
			{
				cur->y += st->W_W;
				cur->count += 1;
			}
		}
	else if ((int)(cur->x + cur->y) + 1 > (int)(cur->x1 + cur->y1))
		while ((int) (cur->x + cur->y) > (int) (cur->x1 + cur->y1) && cur->x + cur->y < st->W_W * st->W_H)
		{
			st->img_data[(int) (cur->x + cur->y)] = color_pix(cur, st, 0x3fcdc7, 0x3f51c7);
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
