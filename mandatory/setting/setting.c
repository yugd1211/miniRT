/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:46 by iyun              #+#    #+#             */
/*   Updated: 2022/09/30 19:01:10 by iyun             ###   ########seoul.kr  */
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

void	set_sphere(char **list, t_object **object, int *count)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new || *count != 8)
		ft_error("set_sphere");
	new->center.x = ft_atof(list[1]);
	new->center.y = ft_atof(list[2]);
	new->center.z = ft_atof(list[3]);
	new->diameter = ft_atof(list[4]);
	new->color.red = ft_atoi(list[5]);
	new->color.green = ft_atoi(list[6]);
	new->color.blue = ft_atoi(list[7]);
	(*object)->object = (void *)new;
	(*object)->object_type = SPHERE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_upper_cent(t_cylinder *cylinder)
{
	t_point	temp;

	temp = cylinder->normal_vec;
	n_multi_vec(cylinder->height, &temp);
	vec_plus_vec(temp, cylinder->under_cent, &(cylinder->upper_cent));
}

void	set_cylinder(char **list, t_object **object, int *count)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new || *count != 12)
		ft_error("set_cylinder");
	new->under_cent.x = ft_atof(list[1]);
	new->under_cent.y = ft_atof(list[2]);
	new->under_cent.z = ft_atof(list[3]);
	new->normal_vec.x = ft_atof(list[4]);
	new->normal_vec.y = ft_atof(list[5]);
	new->normal_vec.z = ft_atof(list[6]);
	new->diameter = ft_atof(list[7]);
	new->height = ft_atof(list[8]);
	new->color.red = ft_atoi(list[9]);
	new->color.green = ft_atoi(list[10]);
	new->color.blue = ft_atoi(list[11]);
	set_upper_cent(new);
	(*object)->object = (void *)new;
	(*object)->object_type = CYLINDER;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_plane(char **list, t_object **object, int *count)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new || *count != 10)
		ft_error("set_plane");
	new->in_plain.x = ft_atof(list[1]);
	new->in_plain.y = ft_atof(list[2]);
	new->in_plain.z = ft_atof(list[3]);
	new->normal_vec.x = ft_atof(list[4]);
	new->normal_vec.y = ft_atof(list[5]);
	new->normal_vec.z = ft_atof(list[6]);
	new->color.red = ft_atoi(list[7]);
	new->color.green = ft_atoi(list[8]);
	new->color.blue = ft_atoi(list[9]);
	(*object)->object = (void *)new;
	(*object)->object_type = PLANE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_cone(char **list, t_object **object, int *count)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new || *count != 12)
		ft_error("set_cone\n");
	new->under_cent.x = ft_atof(list[1]);
	new->under_cent.y = ft_atof(list[2]);
	new->under_cent.z = ft_atof(list[3]);
	new->normal_vec.x = ft_atof(list[4]);
	new->normal_vec.y = ft_atof(list[5]);
	new->normal_vec.z = ft_atof(list[6]);
	new->diameter = ft_atof(list[7]);
	new->height = ft_atof(list[8]);
	new->color.red = ft_atoi(list[9]);
	new->color.green = ft_atoi(list[10]);
	new->color.blue = ft_atoi(list[11]);
	(*object)->object = (void *)new;
	(*object)->object_type = CONE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}
