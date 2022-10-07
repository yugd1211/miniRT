/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_necessity_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:24 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	check_necessity(t_necessity necessity)
{
	if (necessity.light->_switch == ON && necessity.camera._switch == ON \
		&& necessity.ambient._switch == ON)
		return (1);
	return (-1);
}
