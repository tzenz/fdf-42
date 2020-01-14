/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:57:47 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/30 19:57:48 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int 		mouse_release(int button, int x, int y, file *st)
{
	st->button += button;
	return (0);
}

int 		mouse_move(int x, int y, file *st)
{
	mlx_hook(st->win, 5, 0, mouse_release, st);
	if (st->button > 0)
		return (0);
	if (x > st->x)
		st->angle_y += 0.07;
	else if (x < st->x)
		st->angle_y -= 0.07;
	st->x = x;
	st->y = y;
	putclean(st, 0);
	return (0);
}

int 		mouse_press(int button, int x, int y, file *st)
{
	mlx_hook(st->win, 6, 0, mouse_move, st);
	st->button = 0;
	return (0);
}
