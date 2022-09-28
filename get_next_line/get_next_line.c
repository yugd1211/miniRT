/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyun <iyun@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 11:37:51 by iyun              #+#    #+#             */
/*   Updated: 2021/12/27 11:37:56 by iyun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ret_backup(int fd, char *buf, char *backup)
{
	char	*temp;
	int		save;

	save = 1;
	while (save >= 0)
	{
		ft_bzero(buf, BUFFER_SIZE);
		save = read(fd, buf, BUFFER_SIZE);
		if (save == 0)
			break ;
		if (save < 0)
			return (NULL);
		if (backup == NULL)
			backup = ft_strdup("");
		temp = ft_strjoin(backup, buf);
		free(backup);
		backup = ft_strdup(temp);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

char	*ret_line(char **backup)
{
	char	*temp;
	char	*line;
	char	*ttemp;

	if (*backup == NULL)
		return (NULL);
	temp = ft_strchr(*backup, '\n');
	ttemp = *backup;
	if (temp)
	{
		*temp = '\0';
		line = ft_strjoin(*backup, "\n");
		*temp = '\n';
		if (ft_strlen(line) < ft_strlen(*backup))
			*backup = ft_strdup(temp + 1);
		else
			*backup = NULL;
	}
	else
	{
		line = ft_strdup(*backup);
		*backup = NULL;
	}
	free(ttemp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	backup = ret_backup(fd, buf, backup);
	free(buf);
	line = ret_line(&backup);
	return (line);
}
