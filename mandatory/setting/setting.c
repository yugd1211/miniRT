/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:46 by iyun              #+#    #+#             */
/*   Updated: 2022/10/05 22:26:23 by iyun             ###   ########seoul.kr  */
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

void	set_color_type(char **list, t_object **object, int *idx)
{
	if (ft_strncmp(list[(*idx)], "rgb", ft_strlen("rgb") + 1) == 0)
	{
		(*idx)++;
		(*object)->color_type = RGB;
	}
	else if (ft_strncmp(list[(*idx)], "ck", ft_strlen("ck") + 1) == 0)
	{
		(*idx)++;
		(*object)->color_type = CK;
	}
	else if (ft_strncmp(list[(*idx)], "bmp", ft_strlen("bmp") + 1) == 0)
	{
		(*idx)++;
		(*object)->color_type = BMP;
	}
	else
		ft_error("Wrong type");
}

void	set_sphere(char **list, t_object **object, int *count, t_minirt info)
{
	t_sphere	*new;
	int			idx;

	idx = 1;
	new = malloc(sizeof(t_sphere));
	if (!new || *count != 9 || *count != 6 || *count != 8)
		ft_error("set_sphere");
	new->center.x = ft_atof(list[idx++]);
	new->center.y = ft_atof(list[idx++]);
	new->center.z = ft_atof(list[idx++]);
	new->diameter = ft_atof(list[idx++]);
	set_color_type(list, object, &idx);
	if ((*object)->color_type == RGB)
	{
		new->color.red = ft_atoi(list[idx++]);
		new->color.green = ft_atoi(list[idx++]);
		new->color.blue = ft_atoi(list[idx++]);
	}
	else if ((*object)->color_type == BMP)
	{
		(*object)->bmp.img.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
			&(*object)->bmp.img.width, &(*object)->bmp.img.height);
		if (!((*object)->bmp.img.img))
			ft_error("Wrong path");
		(*object)->bmp.img.color = (int *)mlx_get_data_addr((*object)->bmp.img.img, \
		&(*object)->bmp.img.bits_per_pixel, &(*object)->bmp.img.line_length, \
		&(*object)->bmp.img.endian);
		(*object)->bmp.bmp.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
				&(*object)->bmp.bmp.width, &(*object)->bmp.bmp.height);
		if (!((*object)->bmp.bmp.img))
			ft_error("Wrong path");
		(*object)->bmp.bmp.color = (int *)mlx_get_data_addr((*object)->bmp.bmp.img, \
		&(*object)->bmp.bmp.bits_per_pixel, &(*object)->bmp.bmp.line_length, \
		&(*object)->bmp.bmp.endian);
	}
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

void	set_cylinder(char **list, t_object **object, int *count, t_minirt info)
{
	t_cylinder	*new;
	int			idx;

	idx = 1;
	new = malloc(sizeof(t_cylinder));
	if (!new || !(*count == 13 || *count == 15))
		ft_error("set_cylinder");
	new->under_cent.x = ft_atof(list[idx++]);
	new->under_cent.y = ft_atof(list[idx++]);
	new->under_cent.z = ft_atof(list[idx++]);
	new->normal_vec.x = ft_atof(list[idx++]);
	new->normal_vec.y = ft_atof(list[idx++]);
	new->normal_vec.z = ft_atof(list[idx++]);
	new->diameter = ft_atof(list[idx++]);
	new->height = ft_atof(list[idx++]);
	set_color_type(list, object, &idx);
	if ((*object)->color_type == BMP)
	{
		(*object)->bmp.img.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
			&(*object)->bmp.img.width, &(*object)->bmp.img.height);
		if (!((*object)->bmp.img.img))
			ft_error("Wrong path");
		(*object)->bmp.img.color = (int *)mlx_get_data_addr((*object)->bmp.img.img, \
		&(*object)->bmp.img.bits_per_pixel, &(*object)->bmp.img.line_length, \
		&(*object)->bmp.img.endian);
		(*object)->bmp.bmp.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
				&(*object)->bmp.bmp.width, &(*object)->bmp.bmp.height);
		if (!((*object)->bmp.bmp.img))
			ft_error("Wrong path");
		(*object)->bmp.bmp.color = (int *)mlx_get_data_addr((*object)->bmp.bmp.img, \
		&(*object)->bmp.bmp.bits_per_pixel, &(*object)->bmp.bmp.line_length, \
		&(*object)->bmp.bmp.endian);
	}
	new->color.red = ft_atoi(list[idx++]);
	new->color.green = ft_atoi(list[idx++]);
	new->color.blue = ft_atoi(list[idx++]);
	set_upper_cent(new);
	(*object)->object = (void *)new;
	(*object)->object_type = CYLINDER;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_plane(char **list, t_object **object, int *count, t_minirt info)
{
	t_plane	*new;
	int		idx;

	idx = 1;
	new = malloc(sizeof(t_plane));
	if (!new || *count != 8 || *count != 10 || *count != 11)
		ft_error("set_plane");
	new->in_plain.x = ft_atof(list[idx++]);
	new->in_plain.y = ft_atof(list[idx++]);
	new->in_plain.z = ft_atof(list[idx++]);
	new->normal_vec.x = ft_atof(list[idx++]);
	new->normal_vec.y = ft_atof(list[idx++]);
	new->normal_vec.z = ft_atof(list[idx++]);
	set_color_type(list, object, &idx);
	if ((*object)->color_type == RGB)
	{
		new->color.red = ft_atoi(list[idx++]);
		new->color.green = ft_atoi(list[idx++]);
		new->color.blue = ft_atoi(list[idx++]);
	}
	else if ((*object)->color_type == BMP)
	{
		(*object)->bmp.img.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
			&(*object)->bmp.img.width, &(*object)->bmp.img.height);
		if (!((*object)->bmp.img.img))
			ft_error("Wrong path");
		(*object)->bmp.img.color = (int *)mlx_get_data_addr((*object)->bmp.img.img, \
		&(*object)->bmp.img.bits_per_pixel, &(*object)->bmp.img.line_length, \
		&(*object)->bmp.img.endian);
		(*object)->bmp.bmp.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
				&(*object)->bmp.bmp.width, &(*object)->bmp.bmp.height);
		if (!((*object)->bmp.bmp.img))
			ft_error("Wrong path");
		(*object)->bmp.bmp.color = (int *)mlx_get_data_addr((*object)->bmp.bmp.img, \
		&(*object)->bmp.bmp.bits_per_pixel, &(*object)->bmp.bmp.line_length, \
		&(*object)->bmp.bmp.endian);
	}
	(*object)->object = (void *)new;
	(*object)->object_type = PLANE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_cone(char **list, t_object **object, int *count, t_minirt info)
{
	t_cylinder	*new;
	int			idx;

	idx = 1;
	new = malloc(sizeof(t_cylinder));
	if (!new || !(*count == 13 || *count == 15))
		ft_error("set_cone\n");
	new->under_cent.x = ft_atof(list[idx++]);
	new->under_cent.y = ft_atof(list[idx++]);
	new->under_cent.z = ft_atof(list[idx++]);
	new->normal_vec.x = ft_atof(list[idx++]);
	new->normal_vec.y = ft_atof(list[idx++]);
	new->normal_vec.z = ft_atof(list[idx++]);
	new->diameter = ft_atof(list[idx++]);
	new->height = ft_atof(list[idx++]);
	set_color_type(list, object, &idx);
	if ((*object)->color_type == BMP)
	{
		(*object)->bmp.img.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
			&(*object)->bmp.img.width, &(*object)->bmp.img.height);
		if (!((*object)->bmp.img.img))
			ft_error("Wrong path");
		(*object)->bmp.img.color = (int *)mlx_get_data_addr((*object)->bmp.img.img, \
		&(*object)->bmp.img.bits_per_pixel, &(*object)->bmp.img.line_length, \
		&(*object)->bmp.img.endian);
		(*object)->bmp.bmp.img = mlx_xpm_file_to_image(info.window.mlx, list[idx++],
				&(*object)->bmp.bmp.width, &(*object)->bmp.bmp.height);
		if (!((*object)->bmp.bmp.img))
			ft_error("Wrong path");
		(*object)->bmp.bmp.color = (int *)mlx_get_data_addr((*object)->bmp.bmp.img, \
		&(*object)->bmp.bmp.bits_per_pixel, &(*object)->bmp.bmp.line_length, \
		&(*object)->bmp.bmp.endian);
	}
	new->color.red = ft_atoi(list[idx++]);
	new->color.green = ft_atoi(list[idx++]);
	new->color.blue = ft_atoi(list[idx++]);
	(*object)->object = (void *)new;
	(*object)->object_type = CONE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}
