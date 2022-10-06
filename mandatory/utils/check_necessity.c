/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_necessity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:56:28 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_necessity(t_necessity necessity)
{
	if (necessity.light->_switch == ON && necessity.camera._switch == ON \
		&& necessity.ambient._switch == ON)
		return (1);
	return (-1);
}
