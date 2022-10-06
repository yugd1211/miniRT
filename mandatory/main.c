/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:04:49 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 17:23:56 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac, char *av[])
{
	t_minirt	info;

	info.necessity.ambient._switch = OFF;
	info.necessity.camera._switch = OFF;
	info.necessity.light = new_light();
	info.head = new_object();
	if (ac != 2)
		ft_error("Wrong ARG");
	ft_set_mlx_data(&(info.window));
	if (place_objects(av, &info) == -1)
		ft_error(NULL);
	ft_window(&info);
	ft_free(info.head, info.necessity.light);
	return (EXIT_SUCCESS);
}