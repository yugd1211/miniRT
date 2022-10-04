/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:57:55 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 19:38:48 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ret_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ret_min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_distance(t_meet meet_point, t_line line, t_light light)
{
	double	dist;

	dist = distance(meet_point.meet, light.light_point);
	return (dist / sqrt(dot_product(line.dir_vec, line.dir_vec)));
}
