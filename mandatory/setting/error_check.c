/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:32:13 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 21:44:15 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_plane_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 11)
		return ;
	else if ((*object)->color_type == CK && *count == 8)
		return ;
	else if ((*object)->color_type == BMP && *count == 10)
		return ;
	ft_error("set_plane");
}

void	ft_cylinder_cone_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 13)
		return ;
	else if ((*object)->color_type == CK && *count == 13)
		return ;
	else if ((*object)->color_type == BMP && *count == 15)
		return ;
	ft_error("set_cylinder or cone");
}

void	ft_sphere_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 9)
		return ;
	else if ((*object)->color_type == CK && *count == 6)
		return ;
	else if ((*object)->color_type == BMP && *count == 8)
		return ;
	ft_error("set_sphere");
}