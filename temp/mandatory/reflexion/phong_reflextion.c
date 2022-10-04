/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflextion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:54:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/04 12:45:02 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	phong_reflexion(t_meet meet_point, t_light light, t_minirt info, t_phong *draw)
{
	t_point						*normal_vec;
	t_light_view_correlation	correlation;

	t_color						obj_changer;

	normal_vec = ft_normal_vec(meet_point, info);
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
