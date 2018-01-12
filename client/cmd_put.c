/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/12 17:08:47 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int			open_file(char *cmd, int fd)
{
	char			*filename;
	int				file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	file = open(filename, O_WRONLY | O_CREAT | O_EXCL,
			S_IRWXU | S_IRGRP | S_IROTH);
	if (file == -1)
		ft_putendl_fd("ERROR_FD", fd);
	else
		ft_putendl_fd("VERIF_FD", fd);
	return (file);
}

static void			run_put(int fd, int file, int totsize)
{
	char			*buff;
	int				size;
	int				n;

	n = 0;
	buff = malloc(sizeof(char) * totsize);
	if (!buff)
		exit(1);
	while (n < totsize)
	{
		size = recv(fd, buff + n, 4096, 0);
		n += size;
	}
	write(file, buff, totsize);
}

static int			size_file(int fd)
{
	int				size;
	char			*line;

	size = 0;
	if (ft_get_next_line(fd, &line) == 1)
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

void				cmd_put(int fd, char *buf)
{
	int				file;
	int				size;

	// if (alert_message("CLIENT_OK", fd) < 1)
	// 	return ;
	if ((file = open_file(buf, fd)) == -1)
		return ;
	// if (alert_message("TEST_OK", fd) < 1)
	// 	return ;
	if ((size = size_file(fd)) == -1)
		return ;
	run_put(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	close(file);
}
