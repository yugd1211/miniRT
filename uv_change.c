#include "incs/minirt.h"

void spere_uv(t_object object, double *theta, double * pi)
{
	t_sphere	*sphere;
	t_point		unit_vec;
	t_point		sphere_vec;

	sphere = (t_sphere *)object.object;
	set_unit_vec(&sphere->center);
	*theta = acos(-unit_vec.y);
	*pi = atan2(-unit_vec.z, unit_vec.x) + M_PI;
	*theta /= M_PI;
	*pi /= (M_PI * 2);
}

void plane_uv(t_object object, double *theta, double *pi, t_line line)
{
	t_plane	*plane;
	t_point	unit_u;
	t_point	unit_v;
	t_point	cam;
	t_point	cp;

	plane = (t_plane *)object.object;
	// cam = line.dir_vec * t + line.start_point;
	cross_product(cam, plane->normal_vec, &unit_u);
	cross_product(plane->normal_vec, unit_u, &unit_v);
	vec_plus_vec(line.start_point, plane->in_plain, &cp);
	*theta = dot_product(cp, unit_u);
	*pi = dot_product(cp, unit_v);
}

void cylinder_or_cone_uv(t_object object, double *theta, double *pi, t_line line)
{
	t_cylinder	*cylinder;
	t_point		unit_u;
	t_point		unit_v;
	t_point		p;
	t_point		cp;

	cylinder = (t_cylinder *)object.object;
	// p = line.dir_vec * t + line.start_point
	vec_minus_vec(p, cylinder->under_cent, &cp);
	cross_product(cp,cylinder->normal_vec, &unit_u)
	set_unit_vec(&unit_u);
	cross_product(cylinder->normal_vec, unit_u, &unit_v);
	*theta = atan2(-dot_product(cp, unit_v), dot_product(cp, unit_u))+ M_PI;
	*pi = fmod(dot_product(cp, cylinder->normal_vec), 1);
}

int vec3_to_uv(t_object object, t_line line)
{
	double	u;
	double	v;

	if (object.object_type == SPHERE)
		spere_uv(object, &u, &v);
	else if (object.object_type == PLANE)
		plane_uv(object, &u, &v, line);
	else if (object.object_type == CYLINDER && object.object_type == CONE)
		cylinder_or_cone_uv(object, &u, &v, line);
}

t_color checkerboard(double u, double v)
{
	int checkerboard_width;		// 매개변수로 가져올것
	int checkerboard_height;	//
	t_color color;				//

	u * checkerboard_width;
	v * checkerboard_height;
	if ((round(u) + round(v)) % 2 == 1)
		return color;
	else
	{
		color.red = 255;
		color.green = 255;
		color.blue = 255;
		return (color);
	}
}


void image_mapping(double u, double v, t_img texture_img)
{

}

