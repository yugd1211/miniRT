/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:48:07 by iyun              #+#    #+#             */
/*   Updated: 2022/09/27 15:48:09 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	num_th_power_of_ten(size_t num)
{
	size_t	dec;
	size_t	count;

	dec = 1;
	count = 0;
	while (count < num)
	{
		dec *= 10;
		count++;
	}
	return (dec);
}

double	ft_atof(char *str)
{
	double	num;
	size_t	dec_point_num;
	int		i;
	int		sign;

	num = 0;
	dec_point_num = 0;
	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while ('0' <= str[i] && str[i] <= '9')
		num = num * 10 + str[i++] - '0';
	if (str[i++] == '.')
		while ('0' <= str[i] && str[i] <= '9')
		{
			num = num * 10 + str[i++] - '0';
			dec_point_num++;
		}
	num = num / num_th_power_of_ten(dec_point_num);
	return (num * sign);
}
