/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflextion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/04 16:39:33 by gyyu             ###   ########.fr       */
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
	}
	// else
	// 	new_nor_vec = nor_vec;
	// printf("x = %d, y = %d, z = %d\n", bmp.red, bmp.green, bmp.blue);
	temp.x = (double)(bmp.red * 2 - 1);
	temp.y = (double)(bmp.green * 2 - 1);
	temp.z = (double)(bmp.blue * 2 - 1);
	cross_product(nor_vec, temp, &tangent);
	cross_product(tangent, nor_vec, &bitangent);
	new_nor_vec.x = (tangent.x * meet_point.meet.x + bitangent.x * meet_point.meet.y + nor_vec.x * meet_point.meet.z);
	new_nor_vec.y = (tangent.y * meet_point.meet.x + bitangent.y * meet_point.meet.y + nor_vec.y * meet_point.meet.z);
	new_nor_vec.z = (tangent.z * meet_point.meet.x + bitangent.z * meet_point.meet.y + nor_vec.z * meet_point.meet.z);
	return (new_nor_vec);
}

void	phong_reflexion(t_meet meet_point, t_light light, t_minirt info, t_phong *draw)
{
	t_point						*normal_vec;
	t_light_view_correlation	correlation;
	t_color						obj_changer;

	normal_vec = ft_normal_vec(meet_point, info);
	*normal_vec = bmp(*normal_vec, meet_point, info);
	set_unit_vec(normal_vec);
	correlation = ft_correlation(meet_point, light, info, *normal_vec);
	if (correlation == OUT_OUT || correlation == IN_IN)
	{
		obj_changer = img_overay(meet_point, info);
		// obj_changer = checkerboard(meet_point, info);
		disfusion_reflex(coef_disfusion_reflex(meet_point, light, *normal_vec), obj_changer, light.color, &(draw->coloring));
		// disfusion_reflex(coef_disfusion_reflex(meet_point, light, *normal_vec), draw->obj_color, light.color, &(draw->coloring));
		specular_reflex(coef_specular_reflex(meet_point, light, info, *normal_vec), light.color, &(draw->coloring));
	}
	free(normal_vec);
}
