/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:49:05 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:55:41 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*new_object(void)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->object_type = NONE;
	new->object = NULL;
	new->next = NULL;
	return (new);
}

t_light	*new_light(void)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	if (!new)
		ft_error("new_light malloc fail");
	new->_switch = OFF;
	new->next = NULL;
	return (new);
}
