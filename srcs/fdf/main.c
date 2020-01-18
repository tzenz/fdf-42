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

float 		check_zoom(t_file *st)
{
	if (st->width >= 100)
		return (1);
	else if ((st->width >= 48 && st->width <= 50) || st->width == 20)
		return (2);
	else if (st->width == 27 && st->hight == 27)
		return (3);
	else if (st->width == 27)
		return (4);
	else if (st->width == 21 || st->width == 19)
		return (8);
	else if (st->width >= 10 && st->width <= 11)
		return (12);
	return (1);
}

t_file 		*start(int argc, char **argv)
{
	t_file	*st;

	if (argc != 2)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	st = (t_file *)ft_memalloc(sizeof(t_file));
	s_hight(st, argv);
	st->W_W = 2000;
	st->W_H = 1000;
	st->zoom = check_zoom(st);
	st->Skey = (t_key *)ft_memalloc(sizeof(t_key));
	st->Scur = (t_cur *)ft_memalloc(sizeof(t_cur));
	st->Scur->maxz = maxz(st) + MOD(minz(st));
	st->Scur->minz = minz(st);
	st->Skey->my = -50;
	return (st);
}

int 		key(int key, t_file *st)
{
	if (key == 53)
		exit(0);
	if (key == 115)
		st->zoom += (float)0.50;
	if (key == 119 && st->zoom > 1)
		st->zoom -= (float)0.50;

	if (key == 123)
		st->Skey->mx -= 10;
	if (key == 124)
		st->Skey->mx += 10;
	if (key == 126)
		st->Skey->my -= 10;
	if (key == 125)
		st->Skey->my += 10;

	if (key == 89)
		st->Skey->angle_x += 0.0002;
	if (key == 91)
		st->Skey->angle_x -= 0.0002;

	if (key == 86)
		st->Skey->angle_y += 0.01;
	if (key == 87)
		st->Skey->angle_y -= 0.01;

	if (key == 83)
		st->Skey->angle_z += 0.0002;
	if (key == 84)
		st->Skey->angle_z -= 0.0002;
	putclean(st, key, 0);
	return (key);
}

void		putclean(t_file *st, int key, int button)
{
	int 	bse[3];

	if ((key == 115 || button == 4) && st->W_W >= 2000)
	{
		st->W_W += 30;
		st->W_H += 30;
		st->X_IMG -= 15;
		st->Y_IMG -= 15;
	}
	else if ((key == 119 || button == 5) && st->W_W > 2000)
	{
		st->W_W -= 30;
		st->W_H -= 30;
		st->X_IMG += 15;
		st->Y_IMG += 15;
	}
	mlx_destroy_image(st->mlx, st->img_ptr);
	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = (int *)mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st, 0, 0);
	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, st->X_IMG, st->Y_IMG);
}

int 		main(int argc, char **argv)
{
	t_file 	*st;
	int 	bse[3];

	st = start(argc, argv);
//	printf("width - %d hight - %d\n", st->width, st->hight);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, 2000, 1000, "FDF");

	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = (int *)mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st, 0, 0);

	mlx_hook(st->win, 2, 0, key, st);
	mlx_hook(st->win, 4, 0, mouse_press, st);

	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr,0, 0);

	mlx_loop(st->mlx);

	return (0);
}
