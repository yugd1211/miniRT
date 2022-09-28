/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_necessity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:24 by iyun              #+#    #+#             */
/*   Updated: 2022/09/27 15:48:25 by iyun             ###   ########seoul.kr  */
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