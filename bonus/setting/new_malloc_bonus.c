/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_malloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:49:05 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:50:23 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
		ft_error("Wrong Malloc");
	new->_switch = OFF;
	new->next = NULL;
	return (new);
}
