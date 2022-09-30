/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:51:50 by iyun              #+#    #+#             */
/*   Updated: 2022/09/30 19:01:57 by iyun             ###   ########seoul.kr  */
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
# include <mlx.h>

# include <stdio.h>

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
	DOWN_CIRCLE,
	NONE
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
// utils
int			check_necessity(t_necessity necessity);
void		color_set(t_phong *draw);
void		over_color_check(t_color *coloring);
void		ft_type(t_color *coloring, t_meet meet_point);
int			num_th_power_of_ten(size_t num);
double		ft_atof(char *str);
int			overflow_check(int sign);
int			ft_atoi(const char *str);
int			ft_error(char *str);
char		**ft_split(char const *str, char *charset, int *save_num);
double		dot_product(t_point p1, t_point p2);
void		cross_product(t_point p1, t_point p2, t_point *ans);
double		distance(t_point p1, t_point p2);
double		ft_abs(double ans);
double		square(double num);
double		n_square(double num, size_t index);
double		ret_max(double a, double b);
double		ret_min(double a, double b);
int			ft_rounding(double num);
int			ft_distance(t_meet meet_point, t_line line, t_light light);
void		set_unit_vec(t_point *p);
void		n_multi_vec(double n, t_point *p);
void		vec_plus_vec(t_point p1, t_point p2, t_point *ans);
void		vec_minus_vec(t_point p1, t_point p2, t_point *ans);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
//setting
void		ft_light_check(t_minirt info, t_meet meet_point, t_phong *draw);
void		ft_color(t_minirt info, t_line line, int x, int y);
t_object	*new_object(void);
t_light		*new_light(void);
int			set_object(char *temp, t_minirt *info, t_object **temp_obj);
int			place_objects(char **argv, t_minirt *info);
void		set_ambient_lighting(char **list, t_minirt *info, int *count);
void		set_camera(char **list, t_minirt *info, int *count);
void		set_light(char **list, t_minirt *info, int *count);
void		set_sphere(char **list, t_object **object, int *count);
void		set_upper_cent(t_cylinder *cylinder);
void		set_cylinder(char **list, t_object **object, int *count);
void		set_plane(char **list, t_object **object, int *count);
void		set_cone(char **list, t_object **object, int *count);
void		set_base_axis(t_minirt info, t_point *base_axis);
void		ft_set_top_left(t_minirt *info, t_point cent_vec);
void		ft_set_screen(t_minirt *info);
void		ft_window(t_minirt *info);
//reflexion
double						coef_ambient_reflex(t_minirt info);
void						ambient_reflex(double coef, t_color obj_color, t_color *coloring);
void						ambient_light(t_minirt info, t_phong *draw);
double						coef_disfusion_reflex(t_meet meet_point, t_light light, t_point nor_vec);
void						disfusion_reflex(double coef, t_color obj_color, t_color light, t_color *coloring);
t_light_view_correlation	ft_correlation(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec);
void						phong_reflexion(t_meet meet_point, t_light light, t_minirt info, t_phong *draw);
double						coef_specular_reflex(t_meet meet_point, t_light light, t_minirt info, t_point nor_vec);
void						specular_reflex(double coef, t_color light, t_color *coloring);
//get_hit_point
void	renew_parm_t(t_object object, t_meet *meet, t_line line, t_type type);
t_meet	*new_meet(t_minirt info);
void	plane_meet(t_object object, t_meet *meet, t_line line);
void	sphere_meet(t_object object, t_meet *meet, t_line line);
void	cylinder_meet(t_object object, t_meet *meet, t_line line);
void	cone_meet(t_object object, t_meet *meet, t_line line);
//get_next_line
void	ft_bzero(void *ptr, size_t count);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int ch);
char	*ft_strdup(const char *src);
char	*ret_backup(int fd, char *buf, char *backup);
char	*ret_line(char **backup);
char	*get_next_line(int fd);

#endif