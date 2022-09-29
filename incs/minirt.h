/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:51:50 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 19:18:50 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "illustrate.h"
# include "utils.h"
# include "setting.h"
# include "reflexion.h"
# include "get_hit_point.h"
# include <../libmlx/mlx.h>

typedef enum e_switch
{
	ON = 0,
	OFF
}	t_switch;

typedef enum e_light_view_correlation
{
	IN_IN = 0,
	IN_OUT,
	OUT_IN,
	OUT_OUT
}	t_light_view_correlation;

typedef enum e_type
{
	PLANE = 0,
	SPHERE,
	CYLINDER,
	CONE,
	UP_CIRCLE,
	DOWN_CIRCLE
}	t_type;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_ambient
{
	double		ambient_ratio;
	t_color		color;
	t_switch	_switch;
}	t_ambient;

typedef	struct s_camera
{
	t_point		view_point;
	t_point		normal_vec;
	double		fow;
	t_switch	_switch;
}	t_camera;

typedef struct s_light
{
	t_point			light_point;
	double			brightness_ratio;
	t_color			color;
	t_switch		_switch;
	struct	s_light	*next;
}	t_light;

typedef struct s_sphere
{
	t_point	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef	struct s_plane
{
	t_point	in_plain;
	t_point	normal_vec;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	double	diameter;
	double	height;
	t_point	under_cent;
	t_point	upper_cent;
	t_point	normal_vec;
	t_color	color;
}	t_cylinder;

typedef struct s_necessity
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		*light;
}	t_necessity;

typedef struct s_object
{
	void			*object;
	t_type			object_type;
	struct s_object	*next;
}	t_object;

typedef struct s_screen
{
	t_point	vertical_vec;
	t_point	holizon_vec;
	t_point	top_left;
}	t_screen;

typedef struct s_formula_coef
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	max;
	double	min;
}	t_formula_coef;

typedef struct s_minirt
{
	t_object	*head;
	t_necessity necessity;
	t_window	window;
	t_screen	screen;
}	t_minirt;

typedef struct s_solution
{
	double	sol1;
	double	sol2;
}	t_solution;

typedef struct s_line
{
	t_point	start_point;
	t_point	dir_vec;
}	t_line;

typedef struct s_meet
{
	void		*object;
	t_type		object_type;
	t_point		meet;
	t_point		dir_vec;
	double		parm_t;
	double		temp_t;
}	t_meet;

typedef struct s_phong
{
	t_color	coloring;
	t_color	obj_color;
	int		color;
}	t_phong;

void	cylinder_tangent_plane(t_meet meet_point, t_point *nor_vec, t_minirt info);
double	get_alpha(t_meet meet_point, t_minirt info);
void	cone_tangent_plane(t_meet meet_point, t_point *nor_vec, t_minirt info);
t_point	*ft_normal_vec(t_meet meet_point, t_minirt info);

#endif