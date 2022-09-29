/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:52:04 by iyun              #+#    #+#             */
/*   Updated: 2022/09/29 18:59:42 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

int			check_necessity(t_necessity necessity);
void		color_set(t_phong *draw);
void		over_color_check(t_color *coloring);
void		ft_type(t_color *coloring, t_meet meet_point);
int			num_th_power_of_ten(size_t num);
double		ft_atof(char *str);
int			overflow_check(int sign);
int			ft_atoi(const char *str);
int			ft_error(char *str);
static char	**ft_malloc_error(char **tab);
static int	check(char *sep, char c);
static int	str_num(char const *str, char *charset, int *save);
static void	str_save(char const *str, char *charset, char **save_str);
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

#endif