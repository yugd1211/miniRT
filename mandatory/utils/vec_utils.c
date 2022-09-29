/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:44 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 18:59:49 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_unit_vec(t_point *p)
{
	double	sum;

	sum = sqrt((p->x) * (p->x) + (p->y) * (p->y) + (p->z) * (p->z));
	p->x /= sum;
	p->y /= sum;
	p->z /= sum;
}

void	n_multi_vec(double n, t_point *p)
{
	p->x *= n;
	p->y *= n;
	p->z *= n;
}

void	vec_plus_vec(t_point p1, t_point p2, t_point *ans)
{
	ans->x = p1.x + p2.y;
	ans->y = p1.y + p2.y;
	ans->z = p1.z + p2.z;
}

void	vec_minus_vec(t_point p1, t_point p2, t_point *ans)
{
	ans->x = p1.x - p2.y;
	ans->y = p1.y - p2.y;
	ans->z = p1.z - p2.z;
}

