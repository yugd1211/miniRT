/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:49:00 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 13:33:50 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	set_object(char *temp, t_minirt *info, t_object **temp_obj)
{
	char	**temp_list;
	int		count;

	temp_list = ft_split(temp, " \t,", &count);
	if (temp_list == NULL)
		ft_error("Wrong Object Splint");
	if (ft_strncmp(temp_list[0], "A", ft_strlen("A") + 1) == 0)
		set_ambient_lighting(temp_list, info, &count);
	else if (ft_strncmp(temp_list[0], "C", ft_strlen("C") + 1) == 0)
		set_camera(temp_list, info, &count);
	else if (ft_strncmp(temp_list[0], "L", ft_strlen("L") + 1) == 0)
		set_light(temp_list, info, &count);
	else if (ft_strncmp(temp_list[0], "sp", ft_strlen("sp") + 1) == 0)
		set_sphere(temp_list, temp_obj, &count, *info);
	else if (ft_strncmp(temp_list[0], "pl", ft_strlen("pl") + 1) == 0)
		set_plane(temp_list, temp_obj, &count, *info);
	else if (ft_strncmp(temp_list[0], "cy", ft_strlen("cy") + 1) == 0)
		set_cylinder(temp_list, temp_obj, &count, *info);
	else if (ft_strncmp(temp_list[0], "co", ft_strlen("co") + 1) == 0)
		set_cone(temp_list, temp_obj, &count, *info);
	else if (ft_strncmp(temp_list[0], "\n", ft_strlen("\n") + 1) != 0)
		ft_error("Wrong argument");
	ft_split_free(temp_list);
	return (0);
}

int	place_objects(char **argv, t_minirt *info)
{
	int			fd;
	char		*temp;
	t_object	*temp_obj;
	t_light		*temp_light;

	temp_light = info->necessity.light;
	temp_obj = info->head;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Wrong Map");
	temp = get_next_line(fd);
	if (temp == NULL)
		return (-1);
	while (temp != NULL)
	{
		set_object(temp, info, &(info->head));
		free(temp);
		temp = get_next_line(fd);
	}
	info->head = temp_obj;
	if (check_necessity(info->necessity) == -1)
		return (-1);
	close(fd);
	info->necessity.light = temp_light;
	return (0);
}
