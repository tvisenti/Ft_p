/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:43:50 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/16 14:00:40 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		open_file(char *buf)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(buf);
	if ((file = open(filename, O_RDONLY)) == -1)
		return (-1);
	return (file);
}

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

	if ((file = open_file(buf)) == -1)
		return (print_fd_err("\033[31mERROR: get, open returns -1\033[0m", fd));
	if ((fstat(file, &st)) == -1)
		return (print_fd_err("\033[31mERROR: get, fstat returns -1\033[0m", fd));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
	== MAP_FAILED)
		return (print_fd_err("\033[31mERROR: get, mmap returns -1\033[0m", fd));
	if (send_get_server(st, fd, ptr, file) == -1)
		return (print_fd_err("\033[31mERROR: get, fails to send\033[0m", fd));
	ft_putendl_fd("\033[32mSUCCESS: get\033[0m", fd);
	write(fd, "\0", 1);
}
