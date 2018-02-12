/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/12 11:38:06 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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
		n += size;
	}
	write(file, buff, size_max);
	return (1);
}

static void		get_next(int fd)
{
	char		*line;

	if (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
}

void			cmd_get_client(int fd, char *buf)
{
	int			file;
	int			size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
		return (print_error_get_put("open() server side failed", file));
	if ((file = open_file_wronly(buf, fd)) == -1)
	{
		return (print_error_get_put(\
			"Can't create the file, already exists or empty", file));
	}
	if (recv_alert("TEST_OK", fd) < 1)
	{
		close(file);
		return (ft_putendl("\033[32mSUCCESS: get\033[0m"));
	}
	if ((size = size_file(fd)) == -1)
		return (print_error_get_put("Can't send size from client side", file));
	recv_get_client(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	get_next(fd);
	close(file);
}
