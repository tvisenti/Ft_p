/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:43:50 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 17:04:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		send_get_server(struct stat st, int fd, void *ptr, int file)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	write(fd, "\0", 1);
	free(size);
	if (send(fd, ptr, st.st_size, 0) == -1)
		return (-1);
	send(fd, "\0", 1, 0);
	munmap(ptr, st.st_size);
	close(file);
	return (1);
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_read(buf)) == -1)
		return (print_fd_err_int("get [server], open returns -1", fd));
	if ((fstat(file, &st)) == -1)
		return (print_fd_err_int("get [server], fstat returns -1", fd));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
	== MAP_FAILED)
		return (print_fd_err_int("get [server], mmap returns -1", fd));
	if (send_get_server(st, fd, ptr, file) == -1)
		return (print_fd_err_int("get [server], fail to send", fd));
	ft_putendl("\033[32mSUCCESS: get [server]\033[0m");
	ft_putstr("$> ");
	close(file);
	return (1);
}
