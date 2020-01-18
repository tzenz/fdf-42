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

void		isometric(float *x, float *y, t_file *st, float z)
{
	float 	pre_x;
	float 	pre_y;

//	if (z)
//		z = st->ziso;
	pre_x = *x;
	pre_y = *y;
	*x = (pre_x - pre_y) * (float)cos(0.523599);
	*y = -z + (pre_x + pre_y) * (float)sin(0.523599);
}

void		rotate_x(float *y, float *z, t_file *st)
{
	float	pre_y;

	pre_y = *y;
	*y = pre_y * (float)cos(st->Skey->angle_x) + *z * (float)sin(st->Skey->angle_x);
	*z = -pre_y * (float)sin(st->Skey->angle_x) + *z * (float)cos(st->Skey->angle_x);
}

void		rotate_y(float *x, float *z, t_file *st)
{
	float 	pre_x;

	pre_x = *x;
	*x = pre_x * (float)cos(st->Skey->angle_y) + *z * (float)sin(st->Skey->angle_y);
	*z = -pre_x * (float)sin(st->Skey->angle_y) + *z * (float)cos(st->Skey->angle_y);
}

void		rotate_z(float *x, float *y, t_file *st)
{
	float	pre_x;
	float	pre_y;

	pre_x = *x;
	pre_y = *y;
	*x = pre_x * (float)cos(st->Skey->angle_z) - pre_y * (float)sin(st->Skey->angle_z);
	*y = pre_x * (float)sin(st->Skey->angle_z) + pre_y * (float)cos(st->Skey->angle_z);
}