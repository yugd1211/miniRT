/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illustrate.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:27:18 by sielee            #+#    #+#             */
/*   Updated: 2022/09/14 20:17:55 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILLUSTRATE_H
# define ILLUSTRATE_H

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_DESTROY_NOTIFY 17
# define KEY_ESC 53

typedef enum	e_side
{
	WIDTH,
	HEIGHT
}				t_e_side;

typedef struct	s_mlx_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx_data;

typedef struct	s_window
{
	t_mlx_data	mlx_data;
	void		*mlx;
	void		*mlx_win;
	int			win_size[2];
}				t_window;

int		ft_key_press(int keycode, t_window *win);
int		ft_event_red_cross(int keycode);
void	ft_init_mlx_img(t_window *win);

#endif