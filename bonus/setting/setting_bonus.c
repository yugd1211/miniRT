/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:46 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:50:36 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_color_type(char **list, t_object *object, int *idx)
{
	if (ft_strncmp(ft_void_newline(list[(*idx)]), \
		"rgb", ft_strlen("rgb") + 1) == 0)
		object->color_type = RGB;
	else if (ft_strncmp(ft_void_newline(list[(*idx)]), \
		"ck", ft_strlen("ck") + 1) == 0)
		object->color_type = CK;
	else if (ft_strncmp(ft_void_newline(list[(*idx)]), \
		"bmp", ft_strlen("bmp") + 1) == 0)
		object->color_type = BMP;
	else
		ft_error("Wrong Color Type3");
	(*idx)++;
}

void	bump_map_check(t_object **object, char **list, int *idx, t_minirt info)
{
	(*object)->bmp.img.img = mlx_xpm_file_to_image(\
		info.window.mlx, list[(*idx)++], &(*object)->bmp.img.width, \
		&(*object)->bmp.img.height);
	if (!((*object)->bmp.img.img))
		ft_error("Wrong Image File");
	(*object)->bmp.img.color = (int *)mlx_get_data_addr(\
		(*object)->bmp.img.img, &(*object)->bmp.img.bits_per_pixel, \
		&(*object)->bmp.img.line_length, &(*object)->bmp.img.endian);
	(*object)->bmp.bmp.img = mlx_xpm_file_to_image(\
		info.window.mlx, ft_void_newline(list[(*idx)++]), \
		&(*object)->bmp.bmp.width, &(*object)->bmp.bmp.height);
	if (!((*object)->bmp.bmp.img))
		ft_error("Wrong Bump Map File");
	(*object)->bmp.bmp.color = (int *)mlx_get_data_addr(\
		(*object)->bmp.bmp.img, &(*object)->bmp.bmp.bits_per_pixel, \
		&(*object)->bmp.bmp.line_length, &(*object)->bmp.bmp.endian);
}

void	rgb_check(t_color *color, char **list, int *idx)
{
	color->red = ft_atoi(list[(*idx)++]);
	color->green = ft_atoi(list[(*idx)++]);
	color->blue = ft_atoi(list[(*idx)++]);
}
