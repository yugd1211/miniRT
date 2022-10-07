/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:25:21 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 13:22:01 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	ft_event_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->mlx_win);
	exit(0);
}

int	ft_event_red_cross(int keycode)
{
	(void) keycode;
	exit(0);
}

int	ft_key_press(int keycode, t_window *win)
{
	if (keycode == KEY_ESC)
		ft_event_close(win);
	return (0);
}
