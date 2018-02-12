/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:43:50 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/12 13:39:34 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		send_get_server(int fd, struct stat st, void *ptr, int file)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
		return (print_error_gp("can't get size from client side", file));
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		print_fd("\033[32mSUCCESS: get\033[0m", fd);
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
		return (print_error_gp("open() server side failed", file));
	if (recv_alert("WRONLY_OK", fd) < 1)
		return (print_error_gp("open() client side failed", file));
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return (print_error_gp("fstat() server side failed", file));
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (ft_putendl("\033[32mSUCCESS: get\033[0m"));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_get_server(fd, st, ptr, file);
	close(file);
}
