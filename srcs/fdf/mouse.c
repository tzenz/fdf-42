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

int 		mouse_release(int button, int x, int y, t_file *st)
{
	st->button += button;
	return (0);
}

int 		mouse_move(int x, int y, t_file *st)
{
	mlx_hook(st->win, 5, 0, mouse_release, st);
	if (st->button > 0)
		return (0);
	if ((float)x > st->x)
		st->angle_y += 0.07;
	else if ((float)x < st->x)
		st->angle_y -= 0.07;
	if ((float)y > st->y)
		st->angle_x += 0.07;
	else if ((float)y < st->y)
		st->angle_x -= 0.07;
	st->x = (float)x;
	st->y = (float)y;
//	printf("x - %d ms->x - %f\n", x ,st->x);
	putclean(st, 0, 0);
	return (0);
}

int 		mouse_press(int button, int x, int y, t_file *st)
{
	if (button == 1)
		mlx_hook(st->win, 6, 0, mouse_move, st);
	if (button == 4)
	{
		st->zoom += (float) 0.50;
		putclean(st, 0, button);
		return (0);
	}
	if (button == 5 && st->zoom > 1)
	{
		st->zoom -= (float) 0.50;
		putclean(st, 0, button);
		return (0);
	}
	st->button = 0;
	return (0);
}
