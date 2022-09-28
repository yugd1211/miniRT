/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:23:31 by iyun              #+#    #+#             */
/*   Updated: 2022/09/28 17:23:28 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_distance(t_meet meet_point, t_line line, t_light light)
{
	double	dist;

	dist = distance(meet_point.meet, light.light_point);
	return (dist / sqrt(dot_product(line.dir_vec, line.dir_vec)));
}

int	ft_light_check(t_minirt info, t_meet meet_point)
{
	t_object	*temp_object;
	t_light		*temp_light;
	t_meet		*meet;
	t_line		line;

	line.start_point = meet_point.meet;
	temp_object = info.head;
	temp_light = info.necessity.light;
	while (temp_light == NULL)
	{
		meet = new_meet(info);
		vec_minus_vec(info.necessity.light->light_point, meet_point.meet, &(line.dir_vec));
		while (temp_object == NULL)
		{
			if (temp_object->object_type == PLANE)
				plane_meet(*temp_object, meet, line);
			else if (temp_object->object_type == SPHERE)
				sphere_meet(*temp_object, meet, line);
			else if (temp_object->object_type == CYLINDER)
				cylinder_meet(*temp_object, meet, line);
			else if (temp_object->object_type == CONE)
				cone_meet(*temp_object, meet, line);
			else
				ft_error("Wrong object");
			if (meet->parm_t > 0 && meet->parm_t <= ft_distance(meet_point, line, *temp_light))
				break ;
			temp_object = temp_object->next;
		}
		if (meet->parm_t == 0 || meet->parm_t > ft_distance(meet_point, line, *temp_light))
			phong_reflexion(meet_point, temp_light, info);
		free(meet);
		temp_light = temp_light->next;
	}
}//광원과 오브젝 사이에 임의의 오브젝이 있는지 검사;

void	ft_color(t_minirt info, t_line line)
{
	t_object	*temp_object;
	t_meet		*meet;

	temp_object = info.head;
	meet = new_meet(info);
	while (temp_object == NULL)
	{
		if (temp_object->object_type == PLANE)
			plane_meet(*temp_object, meet, line);
		else if (temp_object->object_type == SPHERE)
			sphere_meet(*temp_object, meet, line);
		else if (temp_object->object_type == CYLINDER)
			cylinder_meet(*temp_object, meet, line);
		else if (temp_object->object_type == CONE)
			cone_meet(*temp_object, meet, line);
		else
			ft_error("Wrong object");
		temp_object = temp_object->next;
	}
	if (meet->parm_t == 0)
	{
		ambient_light();//주변광
	}
	free(meet);
}

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

float	ret_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ret_min(float a, float b)
{
	if (a > b)
		return (b);
	return (a);
}

void	cylinder_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cylinder;
	t_point			temp_vec;
	t_formula_coef	coef;
	t_solution		solution;

	cylinder = (t_cylinder *)(object.object);
	set_unit_vec(&(cylinder->normal_vec));
	coef.a = dot_product(line.dir_vec, line.dir_vec) - square(dot_product(line.dir_vec, cylinder->normal_vec));
	vec_minus_vec(line.start_point, cylinder->under_cent, &temp_vec);
	coef.b = dot_product(line.dir_vec, temp_vec) - dot_product(temp_vec, cylinder->normal_vec) * dot_product(line.dir_vec, cylinder->normal_vec);
	coef.c = dot_product(temp_vec, temp_vec) - square(dot_product(temp_vec, cylinder->normal_vec)) - square(cylinder->diameter);
	coef.discriminant = coef.b * coef.b - coef.a * coef.c;
	coef.max = (dot_product(cylinder->under_cent, cylinder->normal_vec) - dot_product(line.start_point, cylinder->normal_vec) + cylinder->height) / dot_product(line.dir_vec, cylinder->normal_vec);
	coef.min = (dot_product(cylinder->under_cent, cylinder->normal_vec) - dot_product(line.start_point, cylinder->normal_vec)) / dot_product(line.dir_vec, cylinder->normal_vec);
	//원기둥과 meet 여부//
	if (coef.discriminant < 0)
		return ;
	//원기둥 몸통//
	meet->temp_t = (coef.b * -1 + sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CYLINDER);
	meet->temp_t = (coef.b * -1 - sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CYLINDER);
	//원기둥 윗면//
	temp_vec = line.dir_vec;
	n_multi_vec(coef.max, &temp_vec);
	vec_plus_vec(temp_vec, line.start_point, &temp_vec);
	if (distance(temp_vec, cylinder->upper_cent) <= cylinder->diameter)
	{
		meet->parm_t = coef.max;
		meet->meet = temp_vec;
		meet->object_type = UP_CIRCLE;
		meet->object = object.object;
	}
	//원기둥 아랫면//
	temp_vec = line.dir_vec;
	n_multi_vec(coef.min, &temp_vec);
	vec_plus_vec(temp_vec, line.start_point, &temp_vec);
	if (distance(temp_vec, cylinder->under_cent) <= cylinder->diameter)
	{
		meet->parm_t = coef.min;
		meet->meet = temp_vec;
		meet->object_type = DOWN_CIRCLE;
		meet->object = object.object;
	}
}

void	cone_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cone;
	t_point			temp_vec;
	t_formula_coef	coef;
	t_solution		solution;
	double			temp;

	cone = (t_cylinder *)(object.object);
	temp = cone->diameter * cone->diameter / cone->height * cone->height;
	coef.a = dot_product(line.dir_vec, line.dir_vec) - (1 + temp) * square(dot_product(line.dir_vec, cone->normal_vec));
	vec_minus_vec(line.start_point, cone->under_cent, &temp_vec);
	coef.b = dot_product(line.dir_vec, temp_vec) + temp * cone->height * dot_product(line.dir_vec, cone->normal_vec) - (1 + temp) * dot_product(temp_vec, cone->normal_vec) * dot_product(line.dir_vec, cone->normal_vec);
	coef.c = dot_product(temp_vec, temp_vec) + 2 * temp * cone->height * dot_product(temp_vec, cone->normal_vec) - (1 + temp) * square(dot_product(temp_vec, cone->normal_vec)) - square(cone->diameter);
	coef.discriminant = coef.b * coef.b - coef.a * coef.c;
	coef.max = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec) + cone->height) / dot_product(line.dir_vec, cone->normal_vec);
	coef.min = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec)) / dot_product(line.dir_vec, cone->normal_vec);
	//원뿔과 meet 여부//
	if (coef.discriminant < 0)
		return ;
	//원뿔 몸통//
	meet->temp_t = (coef.b * -1 + sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CONE);
	meet->temp_t = (coef.b * -1 - sqrt(coef.discriminant)) / coef.a;
	if (ret_min(coef.max, coef.min) <= meet->temp_t && meet->temp_t <= ret_max(coef.max, coef.min) && meet->temp_t > 0 && meet->parm_t > meet->temp_t)
		renew_parm_t(object, meet, line, CONE);
	//원뿔 아랫면//
	temp_vec = line.dir_vec;
	n_multi_vec(coef.min, &temp_vec);
	vec_plus_vec(temp_vec, line.start_point, &temp_vec);
	if (distance(temp_vec, cone->under_cent) <= cone->diameter)
	{
		meet->parm_t = coef.min;
		meet->meet = temp_vec;
		meet->object_type = DOWN_CIRCLE;
		meet->object = object.object;
	}
}
