/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 11:53:18 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/24 11:53:20 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "../libft/include/libft.h"
#include "../minilibx_macos/mlx.h"
#include <stdio.h>

typedef struct		s_file
{
	int 			**s;
	int				length;
	int				hight;
	float 			zoom;

	void			*mlx;
	void			*win;

}					file;

int 		drawline(float x, float y, float x1, float y1, file *st);
void		s_hight(file *st, char **argv);
void		ft_putsnbr(file *st);
void		draw(file *st);

#endif