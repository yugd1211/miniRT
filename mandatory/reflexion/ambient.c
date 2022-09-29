/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:38:37 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 18:39:37 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	coef_ambient_reflex(t_minirt info)
{
	return (info.necessity.ambient.ambient_ratio);
}

void	ambient_reflex(double coef, t_color obj_color, t_color *coloring)
{
	coloring->red = ft_rounding(coef * obj_color.red);
	coloring->green = ft_rounding(coef * obj_color.green);
	coloring->blue = ft_rounding(coef * obj_color.blue);
}

void	ambient_light(t_minirt info, t_phong *draw)
{
	draw->coloring.red = info.necessity.ambient.ambient_ratio * info.necessity.ambient.color.red;
	draw->coloring.green = info.necessity.ambient.ambient_ratio * info.necessity.ambient.color.green;
	draw->coloring.blue = info.necessity.ambient.ambient_ratio * info.necessity.ambient.color.blue;
}
