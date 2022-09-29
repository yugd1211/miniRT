/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:30 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:03:41 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_base_axis(t_minirt info, t_point *base_axis)
{
	if (info.necessity.camera.normal_vec.x == 0 && \
	info.necessity.camera.normal_vec.y == 0 && \
	info.necessity.camera.normal_vec.z != 0)
	{
		base_axis->x = 0;
		base_axis->y = 1;
		base_axis->z = 0;
	}
	else if (info.necessity.camera.normal_vec.x == 0 && \
	info.necessity.camera.normal_vec.y == 0 && \
	info.necessity.camera.normal_vec.z == 0)
		ft_error("NO SCREEN");
	else
	{
		base_axis->x = 0;
		base_axis->y = 0;
		base_axis->z = 1;
	}
}

void	ft_set_top_left(t_minirt *info, t_point cent_vec)
{
	t_point	temp_horizon;
	t_point	temp_vertical;
	t_point	base_axis;

	set_base_axis(*info, &base_axis);
	cross_product(base_axis, info->necessity.camera.normal_vec, &(info->screen.holizon_vec));
	set_unit_vec(&(info->screen.holizon_vec));
	cross_product(info->necessity.camera.normal_vec, info->screen.holizon_vec, &(info->screen.vertical_vec));
	set_unit_vec(&(info->screen.vertical_vec));
	temp_horizon = info->screen.holizon_vec;
	temp_vertical = info->screen.vertical_vec;
	n_multi_vec((info->window.win_size[WIDTH] / 2) * -1, &temp_horizon);
	n_multi_vec((info->window.win_size[HEIGHT] / 2), &temp_vertical);
	vec_plus_vec(cent_vec, temp_horizon, &(info->screen.top_left));
	vec_plus_vec(info->screen.top_left, temp_vertical, &(info->screen.top_left));
}

void	ft_set_screen(t_minirt *info)
{
	double	plane_point_dis;
	t_point temp;

	plane_point_dis = (info->window.win_size[WIDTH] / 2) \
	/ tan(info->necessity.camera.fow);
	set_unit_vec(&(info->necessity.camera.normal_vec));
	temp = info->necessity.camera.normal_vec;
	n_multi_vec(plane_point_dis, &temp);
	ft_set_top_left(info, temp);
}

void	ft_window(t_minirt *info)
{
	int		x;
	int		y;
	t_line	line;

	y = 0;
	line.start_point = info->necessity.camera.view_point;
    ft_init_mlx_img(&(info->window));
	ft_set_screen(info);
	while (y < info->window.win_size[HEIGHT])
	{
		x = 0;
		while (x < info->window.win_size[WIDTH])
		{
			vec_minus_vec(info->screen.top_left, info->necessity.camera.view_point, &(line.dir_vec));
			ft_color(*info, line, x, y);
			x++;
			vec_plus_vec(info->screen.top_left, info->screen.holizon_vec, &(info->screen.top_left));
		}
		y++;
		vec_minus_vec(info->screen.top_left, info->screen.vertical_vec, &(info->screen.top_left));
	}
}