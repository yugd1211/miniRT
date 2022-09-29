/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_point.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:11:48 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:12:57 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_HIT_POINT_H
# define GET_HIT_POINT_H

# include "minirt.h"

void	renew_parm_t(t_object object, t_meet *meet, t_line line, t_type type);
t_meet	*new_meet(t_minirt info);
void	plane_meet(t_object object, t_meet *meet, t_line line);
void	sphere_meet(t_object object, t_meet *meet, t_line line);
void	cylinder_meet(t_object object, t_meet *meet, t_line line);
void	cone_meet(t_object object, t_meet *meet, t_line line);

#endif