/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:04:19 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 13:49:24 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	while_obj(t_meet *meet, t_object *temp, t_line line, t_light_check set)
{
	while (temp->object != NULL)
	{
		ft_check_hit_obj(meet, temp, line);
		if (meet->parm_t > 0 && meet->parm_t <= \
			distance(set.meet_point.meet, set.temp_light.light_point))
			break ;
		temp = temp->next;
	}
}

void	ft_set_obj_color( \
	t_minirt info, t_meet meet_point, t_phong *draw, t_light_check *set)
{
	t_color	obj_change;

	set->meet_point = meet_point;
	obj_change = ft_obj_color(info, meet_point, draw);
	ambient_reflex(coef_ambient_reflex(info), obj_change, &(draw->coloring));
}

void	ft_light_check(t_minirt info, t_meet meet_point, t_phong *draw)
{
	t_object		*temp_object;
	t_light			*temp_light;
	t_meet			*meet;
	t_line			line;
	t_light_check	set;

	line.start_point = meet_point.meet;
	temp_light = info.necessity.light;
	ft_set_obj_color(info, meet_point, draw, &set);
	while (temp_light != NULL)
	{
		temp_object = info.head;
		meet = new_meet(info);
		vec_minus_vec(temp_light->light_point, meet_point.meet, \
		&(line.dir_vec));
		set_unit_vec(&(line.dir_vec));
		set.temp_light = *temp_light;
		while_obj(meet, temp_object, line, set);
		if (meet->parm_t <= 0.00000001 || meet->parm_t > \
		distance(meet_point.meet, temp_light->light_point))
			phong_reflexion(meet_point, *temp_light, info, draw);
		free(meet);
		temp_light = temp_light->next;
	}
}
