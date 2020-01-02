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

void		putclean(file *st)
{
	int 	bpp;
	int 	size_line;
	int 	endian;

	st->img_ptr = mlx_new_image(st->mlx, WIN_WIDTH, WIN_HIGHT);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bpp, &size_line, &endian);
	draw(st);
	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, 0, 0);
}

int 		key(int key, file *st)
{
	if (key == 53)
		exit(0);
	if (key == 115)
		st->zoom += (float)0.5;
	if (key == 119)
		st->zoom -= (float)0.5;
	if (key == 116)
		st->ziso += 1;
	if (key == 121)
		st->ziso -= 1;

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
//	ft_putnbr(key);
	putclean(st);
	return (key);
}

int 		main(int argc, char **argv)
{
	file 	*st;
	int 	bpp;
	int 	size_line;
	int 	endian;

	if (argc != 2)
		return (0);
	st = (file *)ft_memalloc(sizeof(file));
	st->zoom = 7;
	st->angle_x = 1;
	st->ziso = 1;
	s_hight(st, argv);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, WIN_WIDTH, WIN_HIGHT, "FDF");


	st->img_ptr = mlx_new_image(st->mlx, WIN_WIDTH, WIN_HIGHT);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bpp, &size_line, &endian);

	draw(st);

	mlx_hook(st->win, 2, 0, key, st);
//	mlx_hook(st->win, 4, 0, mouse_press, st);

	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, 0, 0);

//	drawp(st);
//	mlx_key_hook(st->win, deal_key, st);
	mlx_loop(st->mlx);
	return (0);
}
