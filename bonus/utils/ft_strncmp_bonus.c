/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyyu <gyyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:10:38 by iyun              #+#    #+#             */
/*   Updated: 2022/10/07 12:43:17 by gyyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;
	unsigned char	*cp1;
	unsigned char	*cp2;

	cp1 = (unsigned char *)s1;
	cp2 = (unsigned char *)s2;
	index = 0;
	while (cp1[index] != '\0' && index < n)
	{
		if (cp1[index] != cp2[index])
		{
			return (cp1[index] - s2[index]);
		}
		index++;
	}
	if (cp1[index] == '\0' && index < n)
	{
		return (cp1[index] - cp2[index]);
	}
	return (0);
}
