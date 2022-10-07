/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:47:46 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:41:28 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_cylinder_coefficient(
	t_line line, t_cylinder *cylinder, t_formula_coef *coef)
{
	t_point	temp_vec;

	coef->a = dot_product(line.dir_vec, line.dir_vec) - \
	square(dot_product(line.dir_vec, cylinder->normal_vec));
	vec_minus_vec(line.start_point, cylinder->under_cent, &temp_vec);
	coef->b = dot_product(line.dir_vec, temp_vec) - \
	dot_product(temp_vec, cylinder->normal_vec) * \
	dot_product(line.dir_vec, cylinder->normal_vec);
	coef->c = dot_product(temp_vec, temp_vec) - \
	square(dot_product(temp_vec, cylinder->normal_vec)) - \
	square(cylinder->diameter);
	coef->discriminant = coef->b * coef->b - coef->a * coef->c;
	coef->max = (dot_product(cylinder->under_cent, cylinder->normal_vec) - \
	dot_product(line.start_point, cylinder->normal_vec) + cylinder->height) / \
	dot_product(line.dir_vec, cylinder->normal_vec);
	coef->min = (dot_product(cylinder->under_cent, cylinder->normal_vec) - \
	dot_product(line.start_point, cylinder->normal_vec)) / \
	dot_product(line.dir_vec, cylinder->normal_vec);
}

void	set_cylinder_side_plane(t_meet *meet, t_formula_coef *coef,
	t_cylinder *cylinder, t_cylinder_set set)
{
	meet->temp_t = (coef->b * -1 + sqrt(coef->discriminant)) / coef->a;
	if (0 <= ft_alpha(meet->temp_t, *cylinder, set.line) && \
	ft_alpha(meet->temp_t, *cylinder, set.line) <= cylinder->height && \
	meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(set.obj, meet, set.line, CYLINDER);
	meet->temp_t = (coef->b * -1 - sqrt(coef->discriminant)) / coef->a;
	if (0 <= ft_alpha(meet->temp_t, *cylinder, set.line) && \
	ft_alpha(meet->temp_t, *cylinder, set.line) <= cylinder->height && \
	meet->temp_t > 0 && (meet->parm_t > meet->temp_t || meet->parm_t == 0))
		renew_parm_t(set.obj, meet, set.line, CYLINDER);
}

void	set_cylinder_up_plane(t_meet *meet, t_formula_coef *coef,
	t_cylinder *cylinder, t_cylinder_set set)
{
	t_point	temp_vec;

	temp_vec = set.line.dir_vec;
	n_multi_vec(coef->max, &temp_vec);
	vec_plus_vec(temp_vec, set.line.start_point, &temp_vec);
	meet->temp_t = coef->max;
	if (distance(temp_vec, cylinder->upper_cent) <= cylinder->diameter && \
		(meet->parm_t > meet->temp_t || meet->parm_t == 0))
	{
		meet->parm_t = coef->max;
		meet->meet = temp_vec;
		meet->object_type = UP_CIRCLE;
		set_meet_color_type(set.obj, meet);
		meet->object = set.obj.object;
	}
}

void	set_cylinder_down_plane(t_meet *meet, t_formula_coef *coef,
	t_cylinder *cylinder, t_cylinder_set set)
{
	t_point	temp_vec;

	temp_vec = set.line.dir_vec;
	n_multi_vec(coef->min, &temp_vec);
	vec_plus_vec(temp_vec, set.line.start_point, &temp_vec);
	meet->temp_t = coef->min;
	if (distance(temp_vec, cylinder->under_cent) <= cylinder->diameter && \
		(meet->parm_t > meet->temp_t || meet->parm_t == 0))
	{
		meet->parm_t = coef->min;
		meet->meet = temp_vec;
		meet->object_type = DOWN_CIRCLE;
		set_meet_color_type(set.obj, meet);
		meet->object = set.obj.object;
	}
}

void	cylinder_meet(t_object object, t_meet *meet, t_line line)
{
	t_cylinder		*cylinder;
	t_formula_coef	coef;
	t_cylinder_set	set;

	cylinder = (t_cylinder *)(object.object);
	set_unit_vec(&(cylinder->normal_vec));
	set_cylinder_coefficient(line, cylinder, &coef);
	set.line = line;
	set.obj = object;
	if (coef.discriminant < 0.00000000)
		return ;
	set_cylinder_side_plane(meet, &coef, cylinder, set);
	if (ft_equal(dot_product(line.dir_vec, cylinder->normal_vec), 0.00) == 1)
	{
		set_cylinder_up_plane(meet, &coef, cylinder, set);
		set_cylinder_down_plane(meet, &coef, cylinder, set);
	}
}
