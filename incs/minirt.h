
#ifndef MINIRT_H
# define MINIRT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "illustrate.h"
# include <../libmlx/mlx.h>

typedef enum e_switch
{
	ON = 0,
	OFF
}	t_switch;

typedef enum e_correlation
{
	IN_IN = 0,
	IN_OUT,
	OUT_IN,
	OUT_OUT
}	t_correlation;

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
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
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

double		square(double num);
char		**ft_split(char const *str, char *charset, int *save_num);
int			ft_atoi(const char *str);
int			ft_error(char *str);
void		ft_bzero(void *ptr, size_t count);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *str, int ch);
char		*ft_strdup(const char *src);
char		*ret_backup(int fd, char *buf, char *backup);
char		*ret_line(char **backup);
char		*get_next_line(int fd);
double		ft_atof(char *str);
t_object	*new_object(void);
void 		set_ambient_lighting(char **list, t_minirt *info, int *count);
void 		set_camera(char **list, t_minirt *info, int *count);
void 		set_light(char **list, t_minirt *info, int *count);
void		set_sphere(char **list, t_object *object, int *count);
double 		dot_product(t_point p1, t_point p2);
void		set_cylinder(char **list, t_object *object, int *count);
void		set_plane(char **list, t_object *object, int *count);
void		set_cone(char **list, t_object *object, int *count);
int			check_necessity(t_necessity necessity);
t_light		*new_light(void);
void		cross_product(t_point p1, t_point p2, t_point *ans);
void		set_unit_vec(t_point *p);
double		distance(t_point p1, t_point p2);
double		abs(double ans);
void		n_multi_vec(double n, t_point *p);
void		vec_plus_vec(t_point p1, t_point p2, t_point *ans);
void		vec_minus_vec(t_point p1, t_point p2, t_point *ans);

#endif