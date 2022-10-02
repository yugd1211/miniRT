/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:49:20 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 19:08:19 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cone_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cone;
	t_point			temp_vec;
	t_formula_coef	coef;
	double			temp;

	cone = (t_cylinder *)(object.object);
	set_unit_vec(&(cone->normal_vec));
	temp = square(cone->diameter) / square(cone->height);
	coef.a = dot_product(line.dir_vec, line.dir_vec) - (1 + temp) * square(dot_product(line.dir_vec, cone->normal_vec));
	vec_minus_vec(line.start_point, cone->under_cent, &temp_vec);
	coef.b = dot_product(line.dir_vec, temp_vec) + temp * cone->height * dot_product(line.dir_vec, cone->normal_vec) - (1 + temp) * dot_product(temp_vec, cone->normal_vec) * dot_product(line.dir_vec, cone->normal_vec);
	coef.c = dot_product(temp_vec, temp_vec) + 2 * temp * cone->height * dot_product(temp_vec, cone->normal_vec) - (1 + temp) * square(dot_product(temp_vec, cone->normal_vec)) - square(cone->diameter);
	coef.discriminant = square(coef.b) - coef.a * coef.c;
	coef.max = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec) + cone->height) / dot_product(line.dir_vec, cone->normal_vec);
	coef.min = (dot_product(cone->under_cent, cone->normal_vec) - dot_product(line.start_point, cone->normal_vec)) / dot_product(line.dir_vec, cone->normal_vec);
	//원뿔과 meet 여부//
	if (coef.discriminant < 0.00000000)
		return ;
	//원뿔 몸통//
	meet->temp_t = (coef.b * -1 + sqrt(coef.discriminant)) / coef.a;
	if (0 <= ft_alpha(meet->temp_t, *cone, line) && ft_alpha(meet->temp_t, *cone, line) <= cone->height && meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(object, meet, line, CONE);
	meet->temp_t = (coef.b * -1 - sqrt(coef.discriminant)) / coef.a;
	if (0 <= ft_alpha(meet->temp_t, *cone, line) && ft_alpha(meet->temp_t, *cone, line) <= cone->height && meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(object, meet, line, CONE);
	//원뿔 아랫면//
	if (ft_equal(dot_product(line.dir_vec, cone->normal_vec), 0.00) == 1)
	{
		temp_vec = line.dir_vec;
		n_multi_vec(coef.min, &temp_vec);
		vec_plus_vec(temp_vec, line.start_point, &temp_vec);
		meet->temp_t = coef.min;
		if (distance(temp_vec, cone->under_cent) <= cone->diameter && meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		{
			meet->parm_t = coef.min;
			meet->meet = temp_vec;
			meet->object_type = DOWN_CIRCLE;
			meet->object = object.object;
		}
	}
}
