/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:04:54 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:04:54 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTING_H
# define SETTING_H

# include "minirt.h"

int			ft_light_check(t_minirt info, t_meet meet_point, t_phong *draw);
void		ft_color(t_minirt info, t_line line, int x, int y);
t_object	*new_object(void);
t_light		*new_light(void);
int			set_object(char *temp, t_minirt *info, t_object *temp_obj);
int			place_objects(char **argv, t_minirt *info);
void		set_ambient_lighting(char **list, t_minirt *info, int *count);
void		set_camera(char **list, t_minirt *info, int *count);
void		set_light(char **list, t_minirt *info, int *count);
void		set_sphere(char **list, t_object *object, int *count);
void		set_upper_cent(t_cylinder *cylinder);
void		set_cylinder(char **list, t_object *object, int *count);
void		set_plane(char **list, t_object *object, int *count);
void		set_cone(char **list, t_object *object, int *count);
void		set_base_axis(t_minirt info, t_point *base_axis);
void		ft_set_top_left(t_minirt *info, t_point cent_vec);
void		ft_set_screen(t_minirt *info);
void		ft_window(t_minirt *info);

#endif