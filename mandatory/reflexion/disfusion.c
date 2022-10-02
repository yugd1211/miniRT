/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disfusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:40:07 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 20:27:32 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	coef_disfusion_reflex(t_meet meet_point, t_light light, t_point nor_vec)
{
	t_point	light_vec;
	double	k_b;

	k_b = 1;
	vec_minus_vec(light.light_point, meet_point.meet, &light_vec);
	set_unit_vec(&light_vec);
	return (dot_product(light_vec, nor_vec) * light.brightness_ratio * k_b);
}

// void	disfusion_reflex(double coef, t_color obj_color, t_color light, t_color *coloring)
// {
// 	coloring->red += lround(ret_min((coef * light.red), obj_color.red));
// 	coloring->green += lround(ret_min((coef * light.red), obj_color.green));
// 	coloring->blue += lround(ret_min((coef * light.red), obj_color.blue));
// }

void	disfusion_reflex(double coef, t_color obj_color, t_color *coloring)
{
	coloring->red += lround(coef * obj_color.red);
	coloring->green += lround(coef * obj_color.green);
	coloring->blue += lround(coef * obj_color.blue);
}
