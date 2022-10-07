/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_or_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:39:46 by gyyu              #+#    #+#             */
/*   Updated: 2022/10/07 12:08:53 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_basic_vec(t_point *basic_vec, t_point normal_vec)
{
	if (normal_vec.y != 0.00 || normal_vec.z != 0.00)
	{
		basic_vec->x = 1;
		basic_vec->y = 0;
		basic_vec->z = 0;
	}
	else if (normal_vec.x != 0.00 || normal_vec.y != 0.00)
	{
		basic_vec->x = 0;
		basic_vec->y = 0;
		basic_vec->z = 1;
	}
	else if (normal_vec.x != 0.00 || normal_vec.z != 0.00)
	{
		basic_vec->x = 0;
		basic_vec->y = 1;
		basic_vec->z = 0;
	}
}

void	set_color(t_color *color, int set_color)
{
	color->red = set_color;
	color->green = set_color;
	color->blue = set_color;
}

t_color	checkerboard(t_meet meet_point, t_minirt info)
{
	double	u;
	double	v;
	t_color	color;

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		if (meet_point.object_type == PLANE)
		{
			u /= (double)(8);
			v /= (double)(4);
		}
		else
		{
			u *= (double)(8);
			v *= (double)(4);
		}
		if ((lround(u) + lround(v)) % 2 == 1)
			set_color(&color, 0);
		else
			set_color(&color, 255);
	}
	else
		color = ((t_cylinder *)(meet_point.object))->color;
	return (color);
}

void	get_color(int rgb, t_color *color)
{
	color->red = ((rgb >> 16) & 0xFF);
	color->green = ((rgb >> 8) & 0xFF);
	color->blue = (rgb & 0xFF);
}

t_color	img_overay(t_meet meet_point, t_minirt info)
{
	double	u;
	double	v;
	t_color	color;

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		if (meet_point.object_type == PLANE)
		{
			u /= (double)(16);
			v /= (double)(8);
		}
		else
		{
			u *= (double)(meet_point.bmp.img.width);
			v *= (double)(meet_point.bmp.img.height);
		}
		get_color(meet_point.bmp.img.color[\
			lround(v) * meet_point.bmp.img.width + lround(u)], &color);
	}
	else
		color = ((t_cylinder *)(meet_point.object))->color;
	return (color);
}
