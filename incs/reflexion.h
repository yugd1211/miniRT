/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:07:47 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:07:47 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFLEXION_H
# define REFLEXION_H

# include "minirt.h"

double						coef_ambient_reflex(t_minirt info);
void						ambient_reflex(double coef, t_color obj_color, t_color *coloring);
void						ambient_light(t_minirt info, t_phong *draw);
double						coef_disfusion_reflex(t_meet meet_point, t_light light, t_point nor_vec);
void						disfusion_reflex(double coef, t_color obj_color, t_color light, t_color *coloring);
t_light_view_correlation	ft_correlation(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec);
void						phong_reflexion(t_meet meet_point, t_light light, t_minirt info, t_phong *draw);
double						coef_specular_reflex(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec);
void						specular_reflex(double coef, t_color light, t_color *coloring);

#endif