/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:27:01 by sielee            #+#    #+#             */
/*   Updated: 2022/09/14 19:56:33 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "illustrate.h"

void	ft_set_mlx_data(t_window *win)
{
	win->win_size[WIDTH] = 1920;
	win->win_size[HEIGHT] = 1080;
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, win->win_size[WIDTH], \
	win->win_size[HEIGHT], "miniRT");
	ft_init_mlx_img(win);
}

void	ft_init_mlx_img(t_window *win)
{
	win->mlx_data.img = mlx_new_image(win->mlx, win->win_size[WIDTH], \
	win->win_size[HEIGHT]);
	win->mlx_data.addr = mlx_get_data_addr(win->mlx_data.img, \
	&win->mlx_data.bits_per_pixel, &win->mlx_data.line_length, \
	&win->mlx_data.endian);
}

void	ft_on_screen(t_window *win)
{
	// ft_set_raw_meet(win);
	// ft_basic_trans_meet(win);
	// ft_draw_object(win);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->mlx_data.img, 0, 0);
	mlx_hook(win->mlx_win, X_EVENT_KEY_PRESS, 0, &ft_key_press, win);
	mlx_hook(win->mlx_win, X_EVENT_KEY_DESTROY_NOTIFY, 0, &ft_event_red_cross, \
	0);
	mlx_loop(win->mlx);
}
