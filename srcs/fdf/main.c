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

t_file 		*start(int argc, char **argv)
{
	t_file	*st;

	if (argc != 2)
	{
		ft_putstr("exit\n");
		exit(0);
	}
	st = (t_file *)ft_memalloc(sizeof(t_file));
	st->W_W = 2000;
	st->W_H = 1000;
	st->zoom = 7;
	st->angle_x = 1;
	st->ziso = 1;
	s_hight(st, argv);
	return (st);
}

void		putclean(t_file *st, int key, int button)
{
	int 	bse[3];

	if ((key == 115 || button == 4) && st->W_W >= 2000)
	{
		st->W_W += 50;
		st->W_H += 50;
		st->X_IMG -= 25;
		st->Y_IMG -= 25;
	}
	else if ((key == 119 || button == 5) && st->W_W > 2000)
	{
		st->W_W -= 50;
		st->W_H -= 50;
		st->X_IMG += 25;
		st->Y_IMG += 25;
	}
	mlx_destroy_image(st->mlx, st->img_ptr);
	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st, 0, 0);
	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, st->X_IMG, st->Y_IMG);
}

int 		key(int key, t_file *st)
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
	putclean(st, key, 0);
	return (key);
}

int 		main(int argc, char **argv)
{
	t_file 	*st;
	int 	bse[3];

	st = start(argc, argv);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, 2000, 1000, "FDF");

	st->img_ptr = mlx_new_image(st->mlx, (int)st->W_W, (int)st->W_H);
	st->img_data = mlx_get_data_addr(st->img_ptr, &bse[0], &bse[1], &bse[2]);
	background(st);
	draw(st, 0, 0);

	mlx_hook(st->win, 2, 0, key, st);
	mlx_hook(st->win, 4, 0, mouse_press, st);

	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr,0, 0);

	mlx_loop(st->mlx);

	return (0);
}

//int 		main(void)
//{
//	int 	a;
//
//	a = 5;
//	printf("%d\n%d\n", a, a >> 16);
//	return (0);
//}

//void		draw(file *st)
//{
//	float 	x;
//	float 	y;
//
//	y = 0;
//	x = 0;
//	while (y < (float)st->hight)
////	while (y < (float)st->hight && y < 1)
//	{
//		x = 0;
//		while (x <(float) st->width)
////		while (x < (float)st->width && x < 1)
//		{
////			if (x < (float)st->width - 1)
////				drawimage(x, y, x + 1, y, st);
////			if (y < (float)st->hight - 1)
////				drawimage(x, y, x, y + 1, st);
//			x++;
//		}
//		y++;
//	}
//	printf("x - %f y - %f\n", x, y);
//}

//void		drawimage(float x, float y, float x1, float y1, file *st)
//{
//	int count;
//	int *b1;
//	float z;
//	float z1;
//	float max;
//	float x_step;
//	float y_step;
//	float wcount;
//
//	count = 1;
//	wcount = 0;
//	z = st->s[(int) y][(int) x];
//	z1 = st->s[(int) y1][(int) x1];
//	st->color = (z || z1) ? 0x01a74e : 0xed6321;
//	b1 = st->img_data;
//
////	rotate(&x, &y, st);
////	rotate(&x1, &y1, st);
////	rotate_x(&y, &z, st);
////	rotate_x(&y1, &z1, st);
////	rotate_y(&x, &z, st);
////	rotate_y(&x1, &z1, st);
////	rotate_z(&y, &z, st);
////	rotate_z(&y1, &z1, st);
//
//	isometric(&x, &y, st, (float) z);
//	isometric(&x1, &y1, st, (float) z1);
//
//	st->i = (x * 4 + 4 * st->W_W * y);
//	st->j = (x1 * 4 + 4 * st->W_W * y1);
//
//	st->i *= st->zoom;
//	st->j *= st->zoom;
//
//	st->i += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
//	st->j += ((st->W_H / 2) * st->W_W) + st->W_W / 2;
//
//	x = (int) st->i % (int)st->W_W;
//	y = (int) st->i / (int)st->W_W;
//	x1 = (int) st->j % (int)st->W_W;
//	y1 = (int) st->j / (int)st->W_W;
//
//	x_step = x1 - x;
//	y_step = y1 - y;
//	max = MAX(MOD(x_step), MOD(y_step));
//	x_step /= max;
//	y_step /= max;
//	y = (y >= 0) ? y * st->W_W : y;
//	y1 = (y1 >= 0) ? y1 * st->W_W : y1;
//	while ((int) (x + y) < (int) (x1 + y1) && x + y < st->W_W * st->W_H)
//	{
//		b1[(int) (x + y)] = st->color;
//		x += x_step;
//		if ((int) (wcount += y_step) == count)
//		{
//			y += st->W_W;
//			count += 1;
//		}
//	}
//}
