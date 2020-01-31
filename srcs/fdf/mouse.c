/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:57:47 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 16:06:06 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mouse_release(int button, int x, int y, t_file *st)
{
	(void)x;
	(void)y;
	(void)button;
	st->m->pressed = 0;
	return (0);
}

int			mouse_press(int button, int x, int y, t_file *st)
{
	(void)x;
	(void)y;
	if (button == 1)
		st->m->pressed = 1;
	if (button == 4)
	{
		st->zoom += 1;
		put_clean(st);
		return (0);
	}
	else if (button == 5 && st->zoom > 1)
	{
		st->zoom -= 1;
		put_clean(st);
		return (0);
	}
	return (0);
}

int			mouse_move(int x, int y, t_file *st)
{
	st->m->prev_x = st->m->x;
	st->m->prev_y = st->m->y;
	st->m->x = x;
	st->m->y = y;
	if (st->m->pressed)
	{
		st->k->angle_y += (x - st->m->prev_x) * 0.002;
		st->k->angle_x += (y - st->m->prev_y) * 0.002;
	}
	put_clean(st);
	return (0);
}

void		mouse_controls(t_file *st)
{
	mlx_hook(st->w->win, 4, 0, mouse_press, st);
	mlx_hook(st->w->win, 5, 0, mouse_release, st);
	mlx_hook(st->w->win, 6, 0, mouse_move, st);
}
