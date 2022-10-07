/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:49:20 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:01:24 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_cone_coefficient(
	t_line line, t_cylinder *cone, t_formula_coef *coef, double *temp)
{
	t_point	temp_vec;

	*temp = square(cone->diameter) / square(cone->height);
	coef->a = dot_product(line.dir_vec, line.dir_vec) - (1 + *temp) * \
	square(dot_product(line.dir_vec, cone->normal_vec));
	vec_minus_vec(line.start_point, cone->under_cent, &temp_vec);
	coef->b = dot_product(line.dir_vec, temp_vec) + *temp * cone->height * \
	dot_product(line.dir_vec, cone->normal_vec) - (1 + *temp) * \
	dot_product(temp_vec, cone->normal_vec) * \
	dot_product(line.dir_vec, cone->normal_vec);
	coef->c = dot_product(temp_vec, temp_vec) + 2 * *temp * cone->height * \
	dot_product(temp_vec, cone->normal_vec) - (1 + *temp) * \
	square(dot_product(temp_vec, cone->normal_vec)) - square(cone->diameter);
	coef->discriminant = square(coef->b) - coef->a * coef->c;
	coef->max = (dot_product(cone->under_cent, cone->normal_vec) - \
	dot_product(line.start_point, cone->normal_vec) + cone->height) / \
	dot_product(line.dir_vec, cone->normal_vec);
	coef->min = (dot_product(cone->under_cent, cone->normal_vec) - \
	dot_product(line.start_point, cone->normal_vec)) / \
	dot_product(line.dir_vec, cone->normal_vec);
}

void	set_cone_side_plane(t_meet *meet, t_formula_coef *coef,
	t_cylinder *cone, t_cylinder_set set)
{
	meet->temp_t = (coef->b * -1 + sqrt(coef->discriminant)) / coef->a;
	if (0 <= ft_alpha(meet->temp_t, *cone, set.line) && \
		ft_alpha(meet->temp_t, *cone, set.line) <= cone->height && \
		meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(set.obj, meet, set.line, CONE);
	meet->temp_t = (coef->b * -1 - sqrt(coef->discriminant)) / coef->a;
	if (0 <= ft_alpha(meet->temp_t, *cone, set.line) && \
		ft_alpha(meet->temp_t, *cone, set.line) <= cone->height && \
		meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(set.obj, meet, set.line, CONE);
}

void	set_cone_down_plane(t_meet *meet, t_formula_coef *coef,
	t_cylinder *cone, t_cylinder_set set)
{
	t_point	temp_vec;

	if (ft_equal(dot_product(set.line.dir_vec, cone->normal_vec), 0.00) == 1)
	{
		temp_vec = set.line.dir_vec;
		n_multi_vec(coef->min, &temp_vec);
		vec_plus_vec(temp_vec, set.line.start_point, &temp_vec);
		meet->temp_t = coef->min;
		if (distance(temp_vec, cone->under_cent) <= cone->diameter && \
			meet->temp_t > 0 && \
			(meet->parm_t > meet->temp_t || meet->parm_t == 0))
		{
			meet->parm_t = coef->min;
			meet->meet = temp_vec;
			meet->object_type = DOWN_CIRCLE;
			set_meet_color_type(set.obj, meet);
			meet->object = set.obj.object;
		}
	}
}

void	cone_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder_set	set;
	t_cylinder		*cone;
	t_formula_coef	coef;
	double			temp;

	cone = (t_cylinder *)(object.object);
	set_unit_vec(&(cone->normal_vec));
	set_cone_coefficient(line, cone, &coef, &temp);
	set.obj = object;
	set.line = line;
	if (coef.discriminant < 0.00000000)
		return ;
	set_cone_side_plane(meet, &coef, cone, set);
	set_cone_down_plane(meet, &coef, cone, set);
}
