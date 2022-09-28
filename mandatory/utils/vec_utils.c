/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:44 by iyun              #+#    #+#             */
/*   Updated: 2022/09/27 17:42:52 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	square(double num)
{
	return (num * num);
}

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

double	distance(t_point p1, t_point p2)
{
	double distance;
	
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) \
	+ pow(p1.z - p2.z, 2));
	return (distance);
}

double	abs(double ans)
{
	if (ans < 0)
		return (ans * -1);
	return (ans);
}