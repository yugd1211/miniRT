/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 00:22:33 by iyun              #+#    #+#             */
/*   Updated: 2022/10/04 14:30:05 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void sphere_uv(double *u, double *v, t_meet meet_point)
{
	t_sphere	*sphere;
	t_point		unit_vec;

	sphere = (t_sphere *)(meet_point.object);
	vec_minus_vec(meet_point.meet, sphere->center, &unit_vec);
	set_unit_vec(&unit_vec);
	*u = atan2(-1 * unit_vec.z, unit_vec.x) + M_PI;
	*v = acos(-1 * unit_vec.y);
	*u /= (M_PI * 2);
	*v /= M_PI;
}

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

void plane_uv(double *u, double *v, t_meet meet_point)
{
	t_plane	*plane;
	t_point	unit_u;
	t_point	unit_v;
	t_point	basic_vec;
	t_point	temp_point;

	plane = (t_plane *)(meet_point.object);
	set_basic_vec(&basic_vec, plane->normal_vec);
	cross_product(plane->normal_vec, basic_vec, &unit_v);
	set_unit_vec(&unit_v);
	cross_product(unit_v, plane->normal_vec, &unit_u);
	set_unit_vec(&unit_u);
	vec_minus_vec(meet_point.meet, plane->in_plain, &temp_point);
	*u = ft_abs(dot_product(temp_point, unit_u));
	*v = ft_abs(dot_product(temp_point, unit_v));
}

void cylinder_or_cone_uv(double *u, double *v, t_meet meet_point, t_minirt info)
{
	t_cylinder	*obj;
	t_point		unit_u;
	t_point		unit_v;
	t_point		basic_vec;
	t_point     p_prime;

	obj = (t_cylinder *)(meet_point.object);
	vec_minus_vec(meet_point.meet, obj->under_cent, &p_prime);
	set_basic_vec(&basic_vec, obj->normal_vec);
	cross_product(obj->normal_vec, basic_vec, &unit_v);
	set_unit_vec(&unit_v);
	cross_product(unit_v, obj->normal_vec, &unit_u);
	set_unit_vec(&unit_u);
	*u = atan2(-1 * dot_product(p_prime, unit_v), dot_product(p_prime, unit_u)) + M_PI;
	*v = dot_product(info.necessity.camera.view_point, obj->normal_vec) \
	- dot_product(obj->under_cent, obj->normal_vec) \
	+ dot_product(meet_point.dir_vec, obj->normal_vec) * meet_point.parm_t;
	*v /= obj->height;
	*u = ft_abs(*u);
	*v = ft_abs(*v);
}

int vec3_to_uv(t_meet meet_point, double *u, double *v, t_minirt info)
{
	if (meet_point.object_type == SPHERE)
		sphere_uv(u, v, meet_point);
	else if (meet_point.object_type == PLANE)
		plane_uv(u, v, meet_point);
	else if (meet_point.object_type == CYLINDER || meet_point.object_type == CONE)
		cylinder_or_cone_uv(u, v, meet_point, info);
	else
		return (1);
	return (0);
}

t_color checkerboard(t_meet meet_point, t_minirt info)
{
	double u;
	double v;
	int checkerboard_width = 8;		// 매개변수로 가져올것
	int checkerboard_height = 4;	//	plane = 1,1 나머지는 원하는대로
	t_color color;				//

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		u /= (double)checkerboard_width;
		v /= (double)checkerboard_height;
		if ((lround(u) + lround(v)) % 2 == 1)
		{
			color.red = 0;
			color.green = 0;
			color.blue = 0;
		}
		else
		{
			color.red = 255;
			color.green = 255;
			color.blue = 255;
		}
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

t_color img_overay(t_meet meet_point, t_minirt info)
{
	double	u;
	double	v;
	t_color	color;

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		u *= (double)info.img.width;
		v *= (double)info.img.height;
		get_color(info.int_color[lround(v) * info.img.width + lround(u)], &color);
	}
	else
		color = ((t_cylinder *)(meet_point.object))->color;
	return (color);
}
