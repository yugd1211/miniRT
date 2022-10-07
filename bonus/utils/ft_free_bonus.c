/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:41:55 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	ft_free(t_object *obj_head, t_light *light_head)
{
	t_object	*temp_obj;
	t_light		*temp_light;

	while (obj_head != NULL)
	{
		temp_obj = obj_head->next;
		free(obj_head->object);
		free(obj_head);
		obj_head = temp_obj;
	}
	while (light_head != NULL)
	{
		temp_light = light_head->next;
		free(light_head);
		light_head = temp_light;
	}
}

void	ft_split_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
}
