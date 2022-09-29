/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tagent_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:05:07 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 18:42:47 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_tangent_plane(t_meet meet_point, t_point *nor_vec, t_minirt info)
{
	t_cylinder	*cylinder;
	t_point		temp_point;
	t_point		temp_vec;

	cylinder = (t_cylinder *)(meet_point.object);
	vec_minus_vec(info.necessity.camera.view_point, cylinder->under_cent, &temp_vec);
	temp_point = cylinder->normal_vec;
	n_multi_vec(dot_product(meet_point.dir_vec, cylinder->normal_vec), &temp_point);
	vec_minus_vec(meet_point.dir_vec, temp_point, &temp_point);
	n_multi_vec(meet_point.parm_t, &temp_point);
	vec_plus_vec(temp_point, temp_vec, &temp_point);
	*nor_vec = temp_point;
	temp_point = cylinder->normal_vec;
	n_multi_vec(dot_product(temp_vec, cylinder->normal_vec), &temp_point);
	vec_minus_vec(*nor_vec, temp_point, nor_vec);
}

double	get_alpha(t_meet meet_point, t_minirt info)
{
	t_cylinder	*cone;
	double		alpha;

	cone = (t_cylinder *)(meet_point.object);
	alpha = dot_product(info.necessity.camera.view_point, cone->normal_vec);
	alpha += meet_point.parm_t * dot_product(meet_point.dir_vec, cone->normal_vec);
	alpha -= dot_product(cone->under_cent, cone->normal_vec);
	return (alpha);
}

void	cone_tangent_plane(t_meet meet_point, t_point *nor_vec, t_minirt info)
{
	t_cylinder	*cone;
	t_point		temp_point;
	t_point		temp_vec;
	double		alpha;
	double		radius;

	cone = (t_cylinder *)(meet_point.object);
	alpha = get_alpha(meet_point, info);
	radius = (cone->diameter * (cone->height - alpha)) / cone->height;
	vec_minus_vec(info.necessity.camera.view_point, cone->under_cent, &temp_vec);
	temp_point = cone->normal_vec;
	n_multi_vec(dot_product(meet_point.dir_vec, cone->normal_vec), &temp_point);
	vec_minus_vec(meet_point.dir_vec, temp_point, &temp_point);
	n_multi_vec(meet_point.parm_t, &temp_point);
	vec_plus_vec(temp_point, temp_vec, &temp_point);
	*nor_vec = temp_point;
	temp_point = cone->normal_vec;
	n_multi_vec(dot_product(temp_vec, cone->normal_vec), &temp_point);
	vec_minus_vec(*nor_vec, temp_point, nor_vec);
	temp_point = cone->normal_vec;
	n_multi_vec(radius, &temp_point);
	n_multi_vec(cone->height - alpha, nor_vec);
	vec_plus_vec(temp_point, *nor_vec, nor_vec);
}

t_point	*ft_normal_vec(t_meet meet_point, t_minirt info)
{
	t_point	*nor_vec;

	nor_vec = malloc(sizeof(t_point));
	if (!nor_vec)
		ft_error("Wrong malloc");
	if (meet_point.object_type == PLANE)
		*nor_vec = ((t_plane *)(meet_point.object))->normal_vec;
	else if (meet_point.object_type == SPHERE)
		vec_minus_vec(meet_point.meet, ((t_sphere *)(meet_point.object))->center, nor_vec);
	else if (meet_point.object_type == UP_CIRCLE)
		*nor_vec = ((t_cylinder *)(meet_point.object))->normal_vec;
	else if (meet_point.object_type == DOWN_CIRCLE)
	{
		*nor_vec = ((t_cylinder *)(meet_point.object))->normal_vec;
		n_multi_vec(-1, nor_vec);
	}
	else if (meet_point.object_type == CYLINDER)
		cylinder_tangent_plane(meet_point, nor_vec, info);
	else if (meet_point.object_type == CONE)
		cone_tangent_plane(meet_point, nor_vec, info);
	return (nor_vec);
}
