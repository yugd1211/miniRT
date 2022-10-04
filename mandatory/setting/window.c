/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:30 by iyun              #+#    #+#             */
/*   Updated: 2022/10/04 05:37:26 by iyun             ###   ########seoul.kr  */
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
	n_multi_vec((info->window.win_size[WIDTH] / 2), &temp_horizon);
	n_multi_vec((info->window.win_size[HEIGHT] / 2), &temp_vertical);
	vec_plus_vec(cent_vec, temp_horizon, &(info->screen.top_left));
	vec_plus_vec(info->screen.top_left, temp_vertical, &(info->screen.top_left));
}

void	ft_set_screen(t_minirt *info)
{
	double	plane_point_dis;
	t_point temp;

	plane_point_dis = (info->window.win_size[WIDTH] / 2) \
	/ tan(info->necessity.camera.fow / 2);
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
	t_point	temp_y;
	t_point	draw;

	y = 0;
	line.start_point = info->necessity.camera.view_point;
	ft_set_screen(info);
	draw = info->screen.top_left;

	info->img.img = mlx_xpm_file_to_image(info->window.mlx, "map-of-the-world.xpm",
			&info->img.width, &info->img.height);
	info->int_color = (int *)mlx_get_data_addr(info->img.img, \
	&info->img.bits_per_pixel, &info->img.line_length, \
	&info->img.endian);

	while (y < info->window.win_size[HEIGHT])
	{
		x = 0;
		while (x < info->window.win_size[WIDTH])
		{
			vec_minus_vec(draw, info->necessity.camera.view_point, &(line.dir_vec));
			ft_color(*info, line, x, y);
			x++;
			vec_minus_vec(draw, info->screen.holizon_vec, &(draw));
		}
		y++;
		temp_y = info->screen.vertical_vec;
		n_multi_vec(y, &temp_y);
		vec_minus_vec(info->screen.top_left, temp_y, &(draw));
	}
	ft_on_screen(&(info->window));
}