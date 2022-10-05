/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflextion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/05 17:09:56 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	bmp(t_point	nor_vec, t_meet meet_point, t_minirt info)
{
	double	u;
	double	v;
	t_point	new_nor_vec;
	t_color	bmp;
	t_point	temp;
	t_point	tangent;
	t_point	bitangent;

	if (vec3_to_uv(meet_point, &u, &v, info) == 0)
	{
		u *= (double)info.bmp.width;
		v *= (double)info.bmp.height;
		// get_color((info.int_bmp[lround(v) * info.bmp.width + lround(u)] * 2) - 1, &bmp);
		get_color(info.int_bmp[lround(v) * info.bmp.width + lround(u)], &bmp);
		temp.x = ((double)(bmp.red) / 255);
		temp.y = ((double)(bmp.green) / 255);
		temp.z = ((double)(bmp.blue) / 255);
		printf("x = %lf, y = %lf, z = %lf\n", temp.x, temp.y, temp.z);
		// set_unit_vec(&temp);
		cross_product(nor_vec, temp, &tangent);
		set_unit_vec(&tangent);
		cross_product(tangent, nor_vec, &bitangent);
		set_unit_vec(&bitangent);
		new_nor_vec.x = (tangent.x * meet_point.meet.x + bitangent.x * meet_point.meet.y + nor_vec.x * meet_point.meet.z);
		new_nor_vec.y = (tangent.y * meet_point.meet.x + bitangent.y * meet_point.meet.y + nor_vec.y * meet_point.meet.z);
		new_nor_vec.z = (tangent.z * meet_point.meet.x + bitangent.z * meet_point.meet.y + nor_vec.z * meet_point.meet.z);
		// printf("x = %lf, y = %lf, z = %lf\n", new_nor_vec.x, new_nor_vec.y, new_nor_vec.z);
	}
	else
		new_nor_vec = nor_vec;
	return (new_nor_vec);
}

void	phong_reflexion(t_meet meet_point, t_light light, t_minirt info, t_phong *draw)
{
	t_point						*normal_vec;
	t_light_view_correlation	correlation;

	t_color	obj_change;

	normal_vec = ft_normal_vec(meet_point, info);
	
	*normal_vec = bmp(*normal_vec, meet_point, info);//
	
	set_unit_vec(normal_vec);
	correlation = ft_correlation(meet_point, light, info, *normal_vec);
	if (correlation == OUT_OUT || correlation == IN_IN)
	{
		// obj_change = checkerboard(meet_point, info);
		obj_change = img_overay(meet_point, info);
		disfusion_reflex(coef_disfusion_reflex(meet_point, light, *normal_vec), obj_change, light.color, &(draw->coloring));
		// disfusion_reflex(coef_disfusion_reflex(meet_point, light, *normal_vec), draw->obj_color, light.color, &(draw->coloring));
		specular_reflex(coef_specular_reflex(meet_point, light, info, *normal_vec), light.color, &(draw->coloring));
	}
	free(normal_vec);
}
