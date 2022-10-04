/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:57:30 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 19:56:19 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	color_set(t_phong *draw)
{
	draw->color = 0 << 24 | draw->coloring.red << 16 | draw->coloring.green << 8 | draw->coloring.blue;
}

void	over_color_check(t_color *coloring)
{
	if (coloring->red > 255)
		coloring->red = 255;
	if (coloring->green > 255)
		coloring->green = 255;
	if (coloring->blue > 255)
		coloring->blue = 255;
}

void	ft_type(t_color *coloring, t_meet meet_point)
{
	if (meet_point.object_type == PLANE)
		*coloring = ((t_plane *)(meet_point.object))->color;
	else if (meet_point.object_type == SPHERE)
		*coloring = ((t_sphere *)(meet_point.object))->color;
	else if (meet_point.object_type == CYLINDER || \
		meet_point.object_type == CONE || meet_point.object_type == UP_CIRCLE \
		|| meet_point.object_type == DOWN_CIRCLE)
		*coloring = ((t_cylinder *)(meet_point.object))->color;
}
