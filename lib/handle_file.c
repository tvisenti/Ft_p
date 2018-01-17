/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:07:12 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 14:36:22 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

int		open_file(char *cmd)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(cmd);
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
		S_IRWXU | S_IRGRP | S_IROTH);
	free(filename);
	return (file);
}

int		open_file_read(char *cmd)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(cmd);
	file = open(filename, O_RDONLY);
	free(filename);
	return (file);
}

int		get_size_file(int fd)
{
	int			size;
	char		*line;

	size = 0;
	if (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		size = ft_atoi(line);
		if (size < 1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	return (size);
}