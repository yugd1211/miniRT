/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:41:21 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:27:04 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	coef_specular_reflex(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec)
{
	t_point	light_vec;
	t_point	camera_vec;
	t_point	temp_vec;
	double	theta;
	double	k_s;

	k_s = 1;
	vec_minus_vec(light.light_point, meet_point.meet, &light_vec);
	set_unit_vec(&light_vec);
	vec_minus_vec(info.necessity.camera.view_point, meet_point.meet, \
	&camera_vec);
	set_unit_vec(&camera_vec);
	temp_vec = nor_vec;
	n_multi_vec(dot_product(nor_vec, light_vec) * 2, &temp_vec);
	vec_minus_vec(temp_vec, light_vec, &temp_vec);
	set_unit_vec(&temp_vec);
	theta = dot_product(temp_vec, camera_vec);
	return (k_s * pow(theta, 64) * light.brightness_ratio);
}

void	specular_reflex(double coef, t_color light, t_color *coloring)
{
	coloring->red += lround(coef * (double)(light.red));
	coloring->green += lround(coef * (double)(light.green));
	coloring->blue += lround(coef * (double)(light.blue));
}
