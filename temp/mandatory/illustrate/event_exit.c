/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sielee <sielee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:03:12 by sielee            #+#    #+#             */
/*   Updated: 2022/09/12 20:12:30 by sielee           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_event_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	exit(0);
}

int	ft_event_red_cross(int keycode)
{
	(void) keycode;
	exit (0);
	return (0);
}

int	ft_key_press(int keycode, t_window *win)
{
	if (keycode == KEY_ESC)
		ft_event_close(win);
	return (0);
}
