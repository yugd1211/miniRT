/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:54:22 by iyun              #+#    #+#             */
/*   Updated: 2022/10/02 18:54:31 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_alpha(double temp, t_cylinder obj, t_line line)
{
	return (dot_product(line.start_point, obj.normal_vec) - dot_product(obj.under_cent, obj.normal_vec) + temp * dot_product(line.dir_vec, obj.normal_vec));
}