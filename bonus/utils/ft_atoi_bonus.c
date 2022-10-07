/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 13:57:40 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	overflow_check(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long long int	num;
	long long int	overflowcheck;
	int				i;
	int				sign;

	num = 0;
	i = 0;
	sign = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while ('0' <= str[i] && str[i] <= '9')
	{
		overflowcheck = num;
		num = num * 10 + str[i++] - '0';
		if (num < overflowcheck)
			return (overflow_check(sign));
	}
	return (num * sign);
}
