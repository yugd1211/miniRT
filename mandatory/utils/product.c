/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:39 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:56:51 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_product(t_point p1, t_point p2)
{
	return ((p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z));
}

void	cross_product(t_point p1, t_point p2, t_point *ans)
{
	ans->x = p1.y * p2.z - p1.z * p2.y;
	ans->y = p1.z * p2.x - p1.x * p2.z;
	ans->z = p1.x * p2.y - p1.y * p2.x;
}
