/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:18:43 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/24 19:18:45 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

file 		*start(int argc, char **argv)
{
	file	*st;

	if (argc != 2)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	st = (file *)ft_memalloc(sizeof(file));
	st->W_W = 2000;
	st->W_H = 1000;
	st->zoom = 10;
	st->angle_x = 1;
	st->ziso = 3;
	s_hight(st, argv);
	return (st);
}

void		putclean(file *st, int key)
{
	int 	bse[3];

	if ((key == 115 && st->W_W >= 2000) || key == 116)
	{
		st->W_W += 10;
		st->W_H += 10;
		st->X_IMG -= 5;
		st->Y_IMG -= 5;
	}
	else if ((key == 119 && st->W_W > 2000) || key == 121)
	{
		st->W_W -= 10;
		st->W_H -= 10;
		st->X_IMG += 5;
		st->Y_IMG += 5;
	}
	printf("W_W - %f W_H - %f\n", st->W_W, st->W_H);
	mlx_destroy_image(st->mlx, st->img_ptr);
	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st);
	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, st->X_IMG, st->Y_IMG);
}

int 		key(int key, file *st)
{
	if (key == 53)
		exit(0);
	if (key == 115)
		st->zoom += (float)0.50;
	if (key == 119 && st->zoom > 1)
		st->zoom -= (float)0.50;
	if (key == 116)
		st->ziso += (float)0.25;
	if (key == 121 && st->ziso > 1)
		st->ziso -= (float)0.25;

	if (key == 89)
		st->angle_x += 0.0002;
	if (key == 91)
		st->angle_x -= 0.0002;

	if (key == 86)
		st->angle_y += 0.01;
	if (key == 87)
		st->angle_y -= 0.01;

	if (key == 83)
		st->angle_z += 0.0002;
	if (key == 84)
		st->angle_z -= 0.0002;
	putclean(st, key);
	return (key);
}

int 		main(int argc, char **argv)
{
	file 	*st;
	int 	bse[3];

	st = start(argc, argv);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, 2000, 1000, "FDF");

	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st);

	mlx_hook(st->win, 2, 0, key, st);
//	mlx_hook(st->win, 4, 0, mouse_press, st);

	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr,0, 0);

	mlx_loop(st->mlx);
	return (0);
}
