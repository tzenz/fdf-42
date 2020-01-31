/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:12:29 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 16:03:05 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		key_3(int key, t_file *st)
{
	if (key == 89)
		st->k->angle_x += 0.05;
	if (key == 91)
		st->k->angle_x -= 0.05;
	if (key == 86)
		st->k->angle_y += 0.05;
	if (key == 87)
		st->k->angle_y -= 0.05;
	if (key == 83)
		st->k->angle_z += 0.05;
	if (key == 84)
		st->k->angle_z -= 0.05;
}

void		key_2(int key, t_file *st)
{
	if (key == 123)
		st->k->mx -= 10;
	if (key == 124)
		st->k->mx += 10;
	if (key == 126)
		st->k->my -= 10;
	if (key == 125)
		st->k->my += 10;
}

int			key_1(int key, t_file *st)
{
	if (key == 53)
		exit(0);
	if (key == 24)
		st->zoom += 2;
	if (key == 27 && st->zoom > 2)
		st->zoom -= 2;
	if (key == 47 && st->ziso < 30)
		st->ziso += 1;
	if (key == 43 && st->ziso > 1)
		st->ziso -= 1;
	key_2(key, st);
	key_3(key, st);
	put_clean(st);
	return (key);
}

void		key_controls(t_file *st)
{
	mlx_hook(st->w->win, 2, 0, key_1, st);
}
