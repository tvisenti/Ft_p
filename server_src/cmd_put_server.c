/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:44:36 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/12 11:51:47 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

static void		get_next(int fd)
{
	char		*line;

	if (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
}

void				cmd_put_server(int fd, char *buf)
{
	int				file;
	int				size;

	file = -1;
	if (recv_alert("RDONLY_OK", fd) < 1)
		return (print_error_get_put("open() client side failed", file));
	if ((file = open_file_wronly(buf, fd)) == -1)
		return (print_error_get_put("Can't create the file already exists", file));
	if (recv_alert("TEST_OK", fd) < 1)
	{
		close(file);
		return (ft_putendl("\033[32mSUCCESS: put\033[0m"));
	}
	if ((size = size_file(fd)) == -1)
		return (print_error_get_put("Can't send size from server side", file));
	recv_put_server(fd, file, size);
	ft_putendl_fd("SUCCESS", fd);
	get_next(fd);
	close(file);
}
