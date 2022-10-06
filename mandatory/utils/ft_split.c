/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:47:15 by iyun              #+#    #+#             */
/*   Updated: 2022/10/06 16:47:16 by iyun             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	check(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	str_num(char const *str, char *charset, int *save)
{
	int	i;
	int	j;
	int	ch_switch;
	int	num;

	i = 0;
	ch_switch = 1;
	num = 0;
	while (str[i] != '\0')
	{
		if (ch_switch == 1 && check(charset, str[i]) == 0)
		{
			j = i;
			while (check(charset, str[j]) != 1 && str[j++] != '\0')
				save[num]++;
			num++;
		}
		if (check(charset, str[i++]) == 1)
			ch_switch = 1;
		else
			ch_switch = 0;
	}
	return (num);
}

static void	str_save(char const *str, char *charset, char **save_str)
{
	int		i;
	int		j;
	int		k;
	int		ch_switch;
	int		num;

	i = 0;
	num = 0;
	ch_switch = 1;
	while (str[i] != '\0')
	{
		if (ch_switch == 1 && check(charset, str[i]) == 0)
		{
			j = i;
			k = 0;
			while (check(charset, str[j]) != 1 && str[j] != '\0')
				save_str[num][k++] = str[j++];
			save_str[num++][k] = '\0';
		}
		if (check(charset, str[i++]) == 1)
			ch_switch = 1;
		else
			ch_switch = 0;
	}
}

char	**ft_split(char const *str, char *charset, int *save_num)
{
	char	**save_str;
	int		save[10000];
	int		i;
	int		num;

	i = 0;
	while (i < 10000)
		save[i++] = 0;
	num = str_num(str, charset, save);
	*save_num = num;
	save_str = (char **)malloc((num + 1) * sizeof(char *));
	if (!(save_str))
		return (NULL);
	save_str[num] = 0;
	i = 0;
	while (i < num)
	{
		save_str[i] = (char *)malloc((save[i] + 1) * sizeof(char));
		if (!save_str[i])
			return (ft_malloc_error(save_str));
		i++;
	}
	str_save(str, charset, save_str);
	return (save_str);
}
