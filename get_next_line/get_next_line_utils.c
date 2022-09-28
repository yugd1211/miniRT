/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:38:05 by iyun              #+#    #+#             */
/*   Updated: 2021/12/27 11:38:13 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_bzero(void *ptr, size_t count)
{
	unsigned int	num;

	num = 0;
	while (num != count)
	{
		((unsigned char *)ptr)[num] = 0;
		num++;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t		num;

	num = 0;
	while (str[num] != '\0')
		num++;
	return (num);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*ptr;
	int		num;

	num = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	while (num < len1)
	{
		ptr[num] = s1[num];
		num++;
	}
	while (num < len1 + len2)
	{
		ptr[num] = s2[num - len1];
		num++;
	}
	ptr[num] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *str, int ch)
{
	int	num;

	num = 0;
	while (str[num] != (char)ch)
	{
		if (str[num] == '\0')
			return (NULL);
		num++;
	}
	return ((char *)&str[num]);
}

char	*ft_strdup(const char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	if (ptr != NULL)
	{
		while (src[i] != '\0')
		{
			ptr[i] = src[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}
