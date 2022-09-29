/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:57:55 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 18:59:16 by iyun             ###   ########seoul.kr  */
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

int	ft_rounding(double num)
{
	int	round_down;

	round_down = (int)num;
	if (num - (double)round_down >= 0.50000000)
		return (round_down + 1);
	return (round_down);
}

int	ft_distance(t_meet meet_point, t_line line, t_light light)
{
	double	dist;

	dist = distance(meet_point.meet, light.light_point);
	return (dist / sqrt(dot_product(line.dir_vec, line.dir_vec)));
}
