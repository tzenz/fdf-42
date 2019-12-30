/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 17:09:22 by tzenz             #+#    #+#             */
/*   Updated: 2019/12/30 17:09:24 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotate_x(float *y, float *z, file *st)
{
	float	pre_y;

	pre_y = *y;
	*y = pre_y * (float)cos(st->angle_x) + *z * (float)sin(st->angle_x);
	*z = -pre_y * (float)sin(st->angle_x) + *z * (float)cos(st->angle_x);
}

void		rotate_y(float *x, float *z, file *st)
{
	float 	pre_x;

	pre_x = *x;
	*x = pre_x * (float)cos(st->angle_y) + *z * (float)sin(st->angle_y);
	*z = -pre_x * (float)sin(st->angle_y) + *z * (float)cos(st->angle_y);
}

void		rotate_z(float *x, float *y, file *st)
{
	float	pre_x;
	float	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = pre_x * (float)cos(st->angle_z) - pre_y * (float)sin(st->angle_z);
	*y = pre_x * (float)sin(st->angle_z) + pre_y * (float)cos(st->angle_z);
}