/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/12 13:39:30 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		send_put_client(struct stat st, int fd, void *ptr, int file)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
		return (print_error_gp("can't get size from server side", file));
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		print_fd("\033[32mSUCCESS: put\033[0m", fd);
}

void			cmd_put_client(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
		return (print_error_gp("open() client side failed", file));
	if (recv_alert("WRONLY_OK", fd) < 1)
		return (print_error_gp("Can't create the file, already exists", file));
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return (print_error_gp("fstat() client side failed", file));
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		close(file);
		return (ft_putendl("\033[32mSUCCESS: put\033[0m"));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_put_client(st, fd, ptr, file);
	close(file);
}
