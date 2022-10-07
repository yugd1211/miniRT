/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:32:13 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:50:08 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	ft_plane_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 11)
		return ;
	else if ((*object)->color_type == CK && *count == 8)
		return ;
	else if ((*object)->color_type == BMP && *count == 10)
		return ;
	ft_error("Wrong Plane Argument");
}

void	ft_cylinder_cone_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 13)
		return ;
	else if ((*object)->color_type == CK && *count == 13)
		return ;
	else if ((*object)->color_type == BMP && *count == 15)
		return ;
	if ((*object)->object_type == CYLINDER)
		ft_error("Wrong Cylinder Argument");
	else
		ft_error("Wrong Cone Argument");
}

void	ft_sphere_error(t_object **object, int *count)
{
	if ((*object)->color_type == RGB && *count == 9)
		return ;
	else if ((*object)->color_type == CK && *count == 6)
		return ;
	else if ((*object)->color_type == BMP && *count == 8)
		return ;
	ft_error("Sphere Argument");
}
