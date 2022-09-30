/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:47:46 by iyun              #+#    #+#             */
/*   Updated: 2022/09/30 15:12:01 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cylinder_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cylinder;
	t_point			temp_vec;
	t_formula_coef	coef;

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