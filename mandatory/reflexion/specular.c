/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:41:21 by iyun              #+#    #+#             */
/*   Updated: 2022/09/30 19:57:00 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	coef_specular_reflex(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec)
{
	t_point	light_vec;
	t_point	camera_vec;
	double	theta;
	double	alpha;
	double	k_s;

	// k_s = pow(distance(light.light_point, meet_point.meet), 1.5);
	k_s = 1;
	vec_minus_vec(light.light_point, meet_point.meet, &light_vec);
	set_unit_vec(&light_vec);
	vec_minus_vec(info.necessity.camera.view_point, meet_point.meet, &camera_vec);
	set_unit_vec(&camera_vec);
	theta = acos(dot_product(light_vec, nor_vec));
	alpha = acos(dot_product(camera_vec, nor_vec));
	return (n_square(cos(ft_abs(theta - alpha)), 64) * light.brightness_ratio * k_s);
}

void	specular_reflex(double coef, t_color light, t_color *coloring)
{
	coloring->red += ft_rounding(coef * light.red);
	coloring->green += ft_rounding(coef * light.green);
	coloring->blue += ft_rounding(coef * light.blue);
}
