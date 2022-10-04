/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:23:31 by iyun              #+#    #+#             */
/*   Updated: 2022/10/04 12:45:06 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_light_check(t_minirt info, t_meet meet_point, t_phong *draw)
{
	t_object	*temp_object;
	t_light		*temp_light;
	t_meet		*meet;
	t_line		line;

	t_color		obj_changer;

	line.start_point = meet_point.meet;
	temp_light = info.necessity.light;
	obj_changer = img_overay(meet_point, info);
	// obj_changer = checkerboard(meet_point, info);
	ambient_reflex(coef_ambient_reflex(info), obj_changer, &(draw->coloring));
	// ambient_reflex(coef_ambient_reflex(info), draw->obj_color, &(draw->coloring));
	while (temp_light != NULL)
	{
		temp_object = info.head;
		meet = new_meet(info);
		vec_minus_vec(temp_light->light_point, meet_point.meet, &(line.dir_vec));
		set_unit_vec(&(line.dir_vec));
		while (temp_object->object != NULL)
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
				ft_error("Wrong object");
			if (meet->parm_t > 0 && meet->parm_t <= distance(meet_point.meet, temp_light->light_point))
				break ;
			temp_object = temp_object->next;
		}
		if (meet->parm_t <= 0.00000001 || meet->parm_t > distance(meet_point.meet, temp_light->light_point))
			phong_reflexion(meet_point, *temp_light, info, draw);
		free(meet);
		temp_light = temp_light->next;
	}
}//광원과 오브젝 사이에 임의의 오브젝이 있는지 검사;

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
		if (temp_object->object_type == PLANE)
			plane_meet(*temp_object, meet, line);
		else if (temp_object->object_type == SPHERE)
			sphere_meet(*temp_object, meet, line);
		else if (temp_object->object_type == CYLINDER)
			cylinder_meet(*temp_object, meet, line);
		else if (temp_object->object_type == CONE)
			cone_meet(*temp_object, meet, line);
		else
			ft_error("Wrong object");
		temp_object = temp_object->next;
	}
	if (ft_equal(meet->parm_t, 0.00) == 0)
		ambient_light(info, &draw);//주변광
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
