/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:09:22 by tzenz             #+#    #+#             */
/*   Updated: 2020/02/01 15:40:52 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		isometric(int *x, int *y, int z)
{
	int		pre_x;
	int		pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = pre_x - pre_y * cos(0.523599);
	*y = -z + (pre_x + pre_y) * sin(0.523599);
}

void		rotate_x(int *y, int *z, double alpha)
{
	int	pre_y;

	pre_y = *y;
	*y = pre_y * cos(alpha) + *z * sin(alpha);
	*z = -pre_y * sin(alpha) + *z * cos(alpha);
}

void		rotate_y(int *x, int *z, double beta)
{
	int		pre_x;

	pre_x = *x;
	*x = pre_x * cos(beta) + *z * sin(beta);
	*z = -pre_x * sin(beta) + *z * cos(beta);
}

void		rotate_z(int *x, int *y, double gamma)
{
	int	pre_x;
	int	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = pre_x * cos(gamma) - pre_y * sin(gamma);
	*y = pre_x * sin(gamma) + pre_y * cos(gamma);
}
