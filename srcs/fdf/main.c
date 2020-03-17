/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:18:43 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/01 17:09:44 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		freest(t_file *st)
{
	int		i;

	i = 0;
	while (i < st->hight)
	{
		free(st->s[i++]);
		st->s[i] = NULL;
	}
	free(st->s);
	st->s = NULL;
	free(st->w);
	free(st->m);
	free(st->k);
	st->w = NULL;
	st->m = NULL;
	st->k = NULL;
	free(st);
	st = NULL;
}

void		put_clean(t_file *st)
{
	int		b[3];

	mlx_destroy_image(st->w->mlx, st->w->i_p);
	st->w->i_p = mlx_new_image(st->w->mlx, WIDTH, HIGHT);
	st->w->i_d = (int *)mlx_get_data_addr(st->w->i_p, &b[0], &b[1], &b[2]);
	background(st);
	draw(st, 0, 0);
	mlx_put_image_to_window(st->w->mlx, st->w->win, st->w->i_p, 0, 0);
	print_menu(st);
}

t_file		*init(int argc, char **argv)
{
	t_file	*st;

	if (argc != 2)
	{
		ft_putstr("Usage:./fdf MAP_FILE\n");
		exit(0);
	}
	st = (t_file *)ft_memalloc(sizeof(t_file));
	readfile(st, argv);
	st->w = (t_window *)ft_memalloc(sizeof(t_window));
	st->m = (t_mouse *)ft_memalloc(sizeof(t_mouse));
	st->k = (t_key *)ft_memalloc(sizeof(t_key));
	st->zoom = MIN((WIDTH - MENU_W) / st->width / 2, HIGHT / st->hight / 2);
	st->maxz = maxz(st) + MOD(minz(st));
	st->minz = minz(st);
	st->ziso = 1;
	st->iso = 1;
	return (st);
}

int			main(int argc, char **argv)
{
	t_file	*st;
	int		b[3];

	st = init(argc, argv);
	st->w->mlx = mlx_init();
	st->w->win = mlx_new_window(st->w->mlx, WIDTH, HIGHT, "FDF");
	st->w->i_p = mlx_new_image(st->w->mlx, WIDTH, HIGHT);
	st->w->i_d = (int *)mlx_get_data_addr(st->w->i_p, &b[0], &b[1], &b[2]);
	background(st);
	draw(st, 0, 0);
	key_controls(st);
	mouse_controls(st);
	mlx_put_image_to_window(st->w->mlx, st->w->win, st->w->i_p, 0, 0);
	print_menu(st);
	mlx_loop(st->w->mlx);
	freest(st);
	return (0);
}
