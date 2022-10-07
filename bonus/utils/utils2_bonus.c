/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:57:55 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	ret_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ret_min(double a, double b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_distance(t_meet meet_point, t_line line, t_light light)
{
	double	dist;

	dist = distance(meet_point.meet, light.light_point);
	return (dist / sqrt(dot_product(line.dir_vec, line.dir_vec)));
}

char	*ft_void_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = 0;
			break ;
		}
		i++;
	}
	return (str);
}
