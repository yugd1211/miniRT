/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_cam_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:25:38 by gyyu              #+#    #+#             */
/*   Updated: 2022/10/06 20:25:42 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_ambient_lighting(char **list, t_minirt *info, int *count)
{
	if (*count != 5 || info->necessity.ambient._switch == ON)
		ft_error("set_ambient_lighting");
	info->necessity.ambient.ambient_ratio = ft_atof(list[1]);
	info->necessity.ambient.color.red = ft_atoi(list[2]);
	info->necessity.ambient.color.green = ft_atoi(list[3]);
	info->necessity.ambient.color.blue = ft_atoi(list[4]);
	info->necessity.ambient._switch = ON;
}

void	set_camera(char **list, t_minirt *info, int *count)
{
	if (*count != 8 || info->necessity.camera._switch == ON)
		ft_error("set_camera");
	info->necessity.camera.view_point.x = ft_atof(list[1]);
	info->necessity.camera.view_point.y = ft_atof(list[2]);
	info->necessity.camera.view_point.z = ft_atof(list[3]);
	info->necessity.camera.normal_vec.x = ft_atof(list[4]);
	info->necessity.camera.normal_vec.y = ft_atof(list[5]);
	info->necessity.camera.normal_vec.z = ft_atof(list[6]);
	info->necessity.camera.fow = ft_atof(list[7]);
	info->necessity.camera._switch = ON;
}

void	set_light(char **list, t_minirt *info, int *count)
{
	if (*count != 8)
		ft_error("set_light");
	if (info->necessity.light != NULL && info->necessity.light->_switch == ON)
	{
		info->necessity.light->next = new_light();
		info->necessity.light = info->necessity.light->next;
	}
	info->necessity.light->light_point.x = ft_atof(list[1]);
	info->necessity.light->light_point.y = ft_atof(list[2]);
	info->necessity.light->light_point.z = ft_atof(list[3]);
	info->necessity.light->brightness_ratio = ft_atof(list[4]);
	info->necessity.light->color.red = ft_atoi(list[5]);
	info->necessity.light->color.green = ft_atoi(list[6]);
	info->necessity.light->color.blue = ft_atoi(list[7]);
	info->necessity.light->_switch = ON;
}
