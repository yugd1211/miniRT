/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:23:31 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:53:30 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	ft_obj_color(t_minirt info, t_meet meet_point, t_phong *draw)
{
	t_color	obj_chance;

	if (meet_point.color_type == CK)
		obj_chance = checkerboard(meet_point, info);
	else if (meet_point.color_type == BMP)
		obj_chance = img_overay(meet_point, info);
	else if (meet_point.color_type == RGB)
		obj_chance = draw->obj_color;
	else
	{
		obj_chance = draw->obj_color;
		ft_error("Wrong Color Type2");
	}
	return (obj_chance);
}

void	ft_check_hit_obj(t_meet *meet, t_object *temp_object, t_line line)
{
	if (temp_object->object_type == PLANE)
		plane_meet(*temp_object, meet, line);
	else if (temp_object->object_type == SPHERE)
		sphere_meet(*temp_object, meet, line);
	else if (temp_object->object_type == CYLINDER)
		cylinder_meet(*temp_object, meet, line);
	else if (temp_object->object_type == CONE)
		cone_meet(*temp_object, meet, line);
	else
		ft_error("Wrong Object Type");
}

void	ft_color(t_minirt info, t_line line, int x, int y)
{
	t_object	*temp_object;
	t_meet		*meet;
	t_phong		draw;

	temp_object = info.head;
	meet = new_meet(info);
	set_unit_vec(&(line.dir_vec));
	while (temp_object->object != NULL)
	{
		ft_check_hit_obj(meet, temp_object, line);
		temp_object = temp_object->next;
	}
	if (ft_equal(meet->parm_t, 0.00) == 0)
		ambient_light(info, &draw);
	else if (meet->parm_t > 0.00000000)
	{
		ft_type(&(draw.obj_color), *meet);
		ft_light_check(info, *meet, &draw);
	}
	over_color_check(&(draw.coloring));
	color_set(&draw);
	my_mlx_pixel_put(&(info.window.mlx_data), x, y, draw.color);
	free(meet);
}
