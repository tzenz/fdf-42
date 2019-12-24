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

int 		main(int argc, char **argv)
{
	file 	*st;

	if (argc != 2)
		return (0);
	st = (file *)ft_memalloc(sizeof(file));
	st->zoom = 20;
	s_hight(st, argv);
	st->mlx = mlx_init();
	st->win= mlx_new_window(st->mlx, 1000, 1000, "FDF");

	draw(st);
//	mlx_key_hook(st->win, deal_key, NULL);
	mlx_loop(st->mlx);
	return (0);
}