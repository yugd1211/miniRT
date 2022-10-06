/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_view_correlation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:37:46 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 20:32:57 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light_view_correlation	ft_correlation(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec)
{
	t_point	meet_camera;
	t_point	meet_light;
	double	inner_normal_light;
	double	inner_normal_view;

	vec_minus_vec(info.necessity.camera.view_point, \
	meet_point.meet, &meet_camera);
	vec_minus_vec(light.light_point, meet_point.meet, &meet_light);
	inner_normal_light = dot_product(meet_light, nor_vec);
	inner_normal_view = dot_product(meet_camera, nor_vec);
	if (inner_normal_light > 0 && inner_normal_view > 0)
		return (OUT_OUT);
	else if (inner_normal_light > 0 && inner_normal_view <= 0)
		return (OUT_IN);
	else if (inner_normal_light <= 0 && inner_normal_view > 0)
		return (IN_OUT);
	return (IN_IN);
} // 빛과 카메라가 오브젝트 내부에 있는지 여부
