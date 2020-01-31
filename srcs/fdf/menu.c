/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:20:19 by tzenz             #+#    #+#             */
/*   Updated: 2020/01/31 16:05:25 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		print_menu(t_file *st)
{
	void	*mlx;
	void	*win;
	int		y;

	y = 0;
	mlx = st->w->mlx;
	win = st->w->win;
	mlx_string_put(mlx, win, 65, y += 20, 0xEAEAEA, "How to use");
	mlx_string_put(mlx, win, 15, y += 35, 0xEAEAEA, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, 0xEAEAEA, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, 0xEAEAEA, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, 0xEAEAEA, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, 0xEAEAEA, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, 0xEAEAEA, "X-Axis - 7/8");
	mlx_string_put(mlx, win, 57, y += 25, 0xEAEAEA, "Y-Axis - 4/5");
	mlx_string_put(mlx, win, 57, y += 25, 0xEAEAEA, "Z-Axis - 1/2");
}
