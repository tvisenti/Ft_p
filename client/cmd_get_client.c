/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 10:22:37 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		open_file(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(cmd);
	if ((file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
		S_IRWXU | S_IRGRP | S_IROTH)) == -1)
		return (-1);
	free(filename);
	return (file);
}

static int		recv_get_client(int fd, int file, int size_max)
{
	char		*buff;
	int			size;
	int			ret;
	
	ret = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	ft_bzero(buff, size_max);
	while (ret < size_max)
	{
		size = recv(fd, buff + ret, 4096, 0);
		if (size % 4096 != 0)
			break ;
		ret += size;
	}
	write(file, buff, size_max);
	return (1);
}

static int		get_size_file(int fd)
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

int			cmd_get_client(int fd, char *buf)
{
	int			file;
	int			size;

	if ((file = open_file(buf, fd)) == -1)
		return (print_error("get, can't open this file"));
	if ((size = get_size_file(fd)) == -1)
		return (print_error("get, file doesn't exist"));
	if (recv_get_client(fd, file, size) == -1)
		return (print_error("get, recv failed"));
	ft_putendl("\033[32mSUCCESS: get\033[0m");
	ft_putstr("$> ");
	close(file);
	return (1);
}