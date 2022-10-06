/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_change.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 00:22:33 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:44:09 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	vec3_to_uv(t_meet meet_point, double *u, double *v, t_minirt info)
{
	if (meet_point.object_type == SPHERE)
		sphere_uv(u, v, meet_point);
	else if (meet_point.object_type == PLANE)
		plane_uv(u, v, meet_point);
	else if (meet_point.object_type == CYLINDER
		|| meet_point.object_type == CONE)
		cylinder_cone_uv(u, v, meet_point, info);
	else
		return (1);
	return (0);
}

void	sphere_uv(double *u, double *v, t_meet meet_point)
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

void	plane_uv(double *u, double *v, t_meet meet_point)
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

void	cylinder_cone_uv(double *u, double *v, t_meet meet_point, t_minirt info)
{
	t_cylinder	*obj;
	t_point		unit_u;
	t_point		unit_v;
	t_point		basic_vec;
	t_point		p_prime;

	obj = (t_cylinder *)(meet_point.object);
	vec_minus_vec(meet_point.meet, obj->under_cent, &p_prime);
	set_basic_vec(&basic_vec, obj->normal_vec);
	cross_product(obj->normal_vec, basic_vec, &unit_v);
	set_unit_vec(&unit_v);
	cross_product(unit_v, obj->normal_vec, &unit_u);
	set_unit_vec(&unit_u);
	*u = atan2(-1 * dot_product(p_prime, unit_v), \
		dot_product(p_prime, unit_u)) + M_PI;
	*v = dot_product(info.necessity.camera.view_point, obj->normal_vec) \
		- dot_product(obj->under_cent, obj->normal_vec) \
		+ dot_product(meet_point.dir_vec, obj->normal_vec) * meet_point.parm_t;
	*v /= obj->height;
	*u = ft_abs(*u);
	*v = ft_abs(*v);
}
