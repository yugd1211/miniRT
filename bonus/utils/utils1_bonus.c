/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:32:51 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:59:22 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	distance(t_point p1, t_point p2)
{
	double	distance;

	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) \
	+ pow(p1.z - p2.z, 2));
	return (distance);
}

double	ft_abs(double ans)
{
	if (ans < 0)
		return (ans * -1);
	return (ans);
}

double	square(double num)
{
	return (num * num);
}

double	n_square(double num, size_t index)
{
	size_t	count;
	double	ret;

	count = 0;
	ret = 1;
	while (count < index)
	{
		ret *= num;
		count++;
	}
	return (ret);
}
