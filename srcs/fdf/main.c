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

int 		key(int key, file *st)
{
	if (key == 53)
		exit(0);
	return (key);
}

int 		mouse_release(int button, int x, int y, file *st)
{
	int 	bpp;
	int 	size_line;
	int 	endian;

	st->x = (float)x;
	st->y = (float)y;

	st->img_ptr = mlx_new_image(st->mlx, WIN_WIDTH, WIN_HIGHT);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bpp, &size_line, &endian);
	draw(st);
	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, 0, 0);
	return (0);
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
	st->zoom = 20;
	s_hight(st, argv);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, WIN_WIDTH, WIN_HIGHT, "FDF");


	st->img_ptr = mlx_new_image(st->mlx, WIN_WIDTH, WIN_HIGHT);
	st->img_data = (int*)mlx_get_data_addr(st->img_ptr, &bpp, &size_line, &endian);

	draw(st);

	mlx_hook(st->win, 2, 0, key, st);
	mlx_hook(st->win, 5, 0, mouse_release, st);

	mlx_put_image_to_window(st->mlx, st->win, st->img_ptr, 0, 0);

//	drawp(st);
//	mlx_key_hook(st->win, deal_key, st);
	mlx_loop(st->mlx);
	return (0);
}
