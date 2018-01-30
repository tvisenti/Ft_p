/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:44:36 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 16:05:57 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int			open_file_put_server(char *cmd, int fd)
{
	char			*filename;
	int				file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	ft_putendl(filename);
	if ((file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
		S_IRWXU | S_IRGRP | S_IROTH)) == -1)
		ft_putendl_fd("ERROR_FD", fd);
	else
		ft_putendl_fd("VERIF_FD", fd);
	return (file);
}

static void			recv_put_server(int fd, int file, int size_max)
{
	char			*buff;
	int				size;
	int				n;

	n = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return ;
	while (n < size_max)
	{
		size = recv(fd, buff + n, 4096, 0);
		if (size % 4096 != 0)
			break ;
		n += size;
	}
	write(file, buff, size_max);
	close(file);
}

static int			size_file(int fd)
{
	int				size;
	char			*line;

	size = 0;
	line = NULL;
	if (get_next_line(fd, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
		{
			ft_putendl(line);
			ft_putendl_fd("ERROR_SIZE", fd);
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

void				cmd_put_server(int fd, char *buf)
{
	int				file;
	int				size;

	if (recv_alert("CLIENT_OK", fd) < 1)
		return (print_error_get_put("open() client side failed"));
	if ((file = open_file_put_server(buf, fd)) == -1)
		return (print_error_get_put("Can't create the file already exists"));
	if (recv_alert("TEST_OK", fd) < 1)
		return (print_error_get_put("Error on server side"));
	if ((size = size_file(fd)) == -1)
		return (print_error_get_put("Can't send size from server side"));
	recv_put_server(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	ft_putendl("\033[32mSUCCESS: put\033[0m");
	close(file);
}
