/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:28:51 by gyyu              #+#    #+#             */
/*   Updated: 2022/10/06 21:42:36 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_sphere(char **list, t_object **object, int *count, t_minirt info)
{
	t_sphere	*new;
	int			idx;

	idx = 1;
	new = malloc(sizeof(t_sphere));
	if (!new || !(*count == 9 || *count == 6 || *count == 8))
		ft_error("set_sphere");
	new->center.x = ft_atof(list[idx++]);
	new->center.y = ft_atof(list[idx++]);
	new->center.z = ft_atof(list[idx++]);
	new->diameter = ft_atof(list[idx++]);
	set_color_type(list, *object, &idx);
	if ((*object)->color_type == RGB)
		rgb_check(&new->color, list, &idx);
	if ((*object)->color_type == BMP)
		bump_map_check(object, list, &idx, info);
	ft_sphere_error(object, count);
	(*object)->object = (void *)new;
	(*object)->object_type = SPHERE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}

void	set_upper_cent(t_cylinder *cylinder)
{
	t_point	temp;

	temp = cylinder->normal_vec;
	set_unit_vec(&temp);
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
	set_color_type(list, *object, &idx);
	if ((*object)->color_type == BMP)
		bump_map_check(object, list, &idx, info);
	ft_cylinder_cone_error(object, count);
	rgb_check(&new->color, list, &idx);
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
	if (!new || !(*count == 8 || *count == 10 || *count == 11))
		ft_error("set_plane");
	new->in_plain.x = ft_atof(list[idx++]);
	new->in_plain.y = ft_atof(list[idx++]);
	new->in_plain.z = ft_atof(list[idx++]);
	new->normal_vec.x = ft_atof(list[idx++]);
	new->normal_vec.y = ft_atof(list[idx++]);
	new->normal_vec.z = ft_atof(list[idx++]);
	set_color_type(list, *object, &idx);
	if ((*object)->color_type == RGB)
		rgb_check(&new->color, list, &idx);
	if ((*object)->color_type == BMP)
		bump_map_check(object, list, &idx, info);
	ft_plane_error(object, count);
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
	set_color_type(list, *object, &idx);
	if ((*object)->color_type == BMP)
		bump_map_check(object, list, &idx, info);
	ft_cylinder_cone_error(object, count);
	rgb_check(&new->color, list, &idx);
	(*object)->object = (void *)new;
	(*object)->object_type = CONE;
	(*object)->next = new_object();
	(*object) = (*object)->next;
}
