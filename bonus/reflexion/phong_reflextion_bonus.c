/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflextion_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_point	get_new_normal_vec(t_point nor_vec, t_point	temp)
{
	t_point	new_nor_vec;
	t_point	tangent;
	t_point	bitangent;
	t_point	basic_vec;

	set_basic_vec(&basic_vec, nor_vec);
	cross_product(nor_vec, basic_vec, &tangent);
	set_unit_vec(&tangent);
	cross_product(tangent, nor_vec, &bitangent);
	set_unit_vec(&bitangent);
	new_nor_vec.x = \
		(tangent.x * temp.x + bitangent.x * temp.y + nor_vec.x * temp.z);
	new_nor_vec.y = \
		(tangent.y * temp.x + bitangent.y * temp.y + nor_vec.y * temp.z);
	new_nor_vec.z = \
		(tangent.z * temp.x + bitangent.z * temp.y + nor_vec.z * temp.z);
	set_unit_vec(&new_nor_vec);
	return (new_nor_vec);
}

void	bmp_size_tuning(t_meet *meet_point, double *u, double *v)
{
	if (meet_point->object_type == PLANE)
	{
		*u /= (double)(16);
		*v /= (double)(8);
	}
	else
	{
		*u *= (double)(meet_point->bmp.img.width);
		*v *= (double)(meet_point->bmp.img.height);
	}
}

t_point	bmp(t_point nor_vec, t_meet meet_point, t_minirt info)
{
	double	u;
	double	v;
	t_point	new_nor_vec;
	t_color	bmp;
	t_point	temp;

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		bmp_size_tuning(&meet_point, &u, &v);
		get_color(meet_point.bmp.bmp.color[lround(v) * \
		meet_point.bmp.bmp.width + lround(u)], &bmp);
		temp.x = (((double)(bmp.red)) / 255 * 2 - 1);
		temp.y = (((double)(bmp.green)) / 255 * 2 - 1);
		temp.z = (((double)(bmp.blue)) / 255 * 2 - 1);
		set_unit_vec(&temp);
		new_nor_vec = get_new_normal_vec(nor_vec, temp);
	}
	else
		new_nor_vec = nor_vec;
	return (new_nor_vec);
}

void	phong_reflexion( \
	t_meet meet_point, t_light light, t_minirt info, t_phong *draw)
{
	t_point						*normal_vec;
	t_light_view_correlation	correlation;
	t_color						obj_change;

	normal_vec = ft_normal_vec(meet_point, info);
	set_unit_vec(normal_vec);
	correlation = ft_correlation(meet_point, light, info, *normal_vec);
	if (correlation == OUT_OUT || correlation == IN_IN)
	{
		if (meet_point.color_type == BMP)
			*normal_vec = bmp(*normal_vec, meet_point, info);
		obj_change = ft_obj_color(info, meet_point, draw);
		disfusion_reflex(coef_disfusion_reflex(meet_point, light, \
		*normal_vec), obj_change, light.color, &(draw->coloring));
		specular_reflex(coef_specular_reflex(meet_point, light, \
		info, *normal_vec), light.color, &(draw->coloring));
	}
	free(normal_vec);
}
