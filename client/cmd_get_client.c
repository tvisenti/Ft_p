/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 10:54:37 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		open_file_get_client(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
		S_IRWXU | S_IRGRP | S_IROTH)) == -1)
		ft_putendl_fd("ERROR_FD", fd);
	else
		ft_putendl_fd("VERIF_FD", fd);
	return (file);
}

static int		recv_get_client(int fd, int file, int size_max)
{
	char		*buff;
	int			size;
	int			n;

	n = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	while (n < size_max)
	{
		size = recv(fd, buff + n, 4096, 0);
		if (size % 4096 != 0)
			break ;
		n += size;
	}
	write(file, buff, size_max);
	return (1);
}

static int		size_file(int fd)
{
	int			size;
	char		*line;

	size = 0;
	line = NULL;
	if (get_next_line(fd, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
		{
			ft_putendl(line);
			ft_putendl_fd("ERROR_FILESIZE", fd);
			free(line);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	ft_putendl_fd("SEND", fd);
	return (size);
}

static void		get_next(int fd)
{
	char		*line;

	if (ft_get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
}

void			cmd_get_client(int fd, char *buf)
{
	int			file;
	int			size;

	if (recv_alert("SERVER_OK", fd) < 1)
		return (print_error_get_put("open() server side failed"));
	if ((file = open_file_get_client(buf, fd)) == -1)
		return (print_error_get_put("Can't create the file, already exists"));
	if (recv_alert("TEST_OK", fd) < 1)
		return (print_error_get_put("mmap() server side failed"));
	if ((size = size_file(fd)) == -1)
		return (print_error_get_put("Can't send size from client side"));
	recv_get_client(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	get_next(fd);
	close(file);
	ft_putstr("$> ");
}
