/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:38:37 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	coef_ambient_reflex(t_minirt info)
{
	return (info.necessity.ambient.ambient_ratio);
}

void	ambient_reflex(double coef, t_color obj_color, t_color *coloring)
{
	coloring->red = lround(coef * (double)(obj_color.red));
	coloring->green = lround(coef * (double)(obj_color.green));
	coloring->blue = lround(coef * (double)(obj_color.blue));
}

void	ambient_light(t_minirt info, t_phong *draw)
{
	draw->coloring.red = lround(info.necessity.ambient.ambient_ratio * \
	info.necessity.ambient.color.red);
	draw->coloring.green = lround(info.necessity.ambient.ambient_ratio * \
	info.necessity.ambient.color.green);
	draw->coloring.blue = lround(info.necessity.ambient.ambient_ratio * \
	info.necessity.ambient.color.blue);
}
