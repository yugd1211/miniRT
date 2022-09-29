/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:46:45 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:12:27 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	renew_parm_t(t_object object, t_meet *meet, t_line line, t_type type)
{
	meet->parm_t = meet->temp_t;
	meet->meet = line.dir_vec;
	n_multi_vec(meet->temp_t, &(meet->meet));
	vec_plus_vec(meet->meet, line.start_point, &(meet->meet));
	meet->dir_vec = line.dir_vec;
	meet->object = object.object;
	meet->object_type = type;
}

t_meet	*new_meet(t_minirt info)
{
	t_meet	*new;

	new = malloc(sizeof(t_meet));
	if (!new)
		ft_error("Wrong malloc");
	new->object = NULL;
	new->parm_t = 0;
	new->meet = info.necessity.camera.view_point;
}

void	plane_meet(t_object object, t_meet *meet, t_line line)
{
	t_plane	*plane;

	plane = (t_plane *)(object.object);
	set_unit_vec(&(plane->normal_vec));
	if (dot_product(plane->normal_vec, line.dir_vec) == 0)
		return ;
	else
	{
		meet->temp_t = dot_product(plane->normal_vec, plane->in_plain) - \
		dot_product(plane->normal_vec, line.start_point) / \
		dot_product(plane->normal_vec, line.dir_vec);
		if (meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		{
			meet->parm_t = meet->temp_t;
			meet->meet = line.dir_vec;
			n_multi_vec(meet->temp_t, &(meet->meet));
			vec_plus_vec(meet->meet, line.start_point, &(meet->meet));
			meet->dir_vec = line.dir_vec;
			meet->object = object.object;
			meet->object_type = PLANE;
		}
	}

}

void	sphere_meet(t_object object, t_meet *meet, t_line line)
{
	t_sphere		*sphere;
	t_point			temp_vec;
	t_formula_coef	coef;

	sphere = (t_sphere *)(object.object);
	coef.a = dot_product(line.dir_vec, line.dir_vec);
	vec_minus_vec(line.start_point, sphere->center, &temp_vec);
	coef.b = dot_product(line.dir_vec, temp_vec);
	coef.c = dot_product(temp_vec, temp_vec) - square(sphere->diameter);
	coef.discriminant = coef.b * coef.b - coef.a * coef.c;
	if (coef.discriminant < 0 || sqrt(coef.discriminant) - coef.b < 0)
		return ;
	else if (sqrt(coef.discriminant) * -1 - coef.b < 0)
	{
		meet->temp_t = (sqrt(coef.discriminant) - coef.b) / coef.a;
		if (meet->parm_t > meet->temp_t)
			renew_parm_t(object, meet, line, SPHERE);
	}
	else
	{
		meet->temp_t = sqrt(coef.discriminant) * -1 - coef.b / coef.a;
		if (meet->parm_t > meet->temp_t)
			renew_parm_t(object, meet, line, SPHERE);
	}
}