/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:43:50 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 11:12:51 by tvisenti         ###   ########.fr       */
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
	free(filename);
	return (file);
}

static int		send_get_server(struct stat st, int fd, void *ptr)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	write(fd, "\0", 1);
	free(size);
	if (send(fd, ptr, st.st_size, 0) == -1)
		return (-1);
	munmap(ptr, st.st_size);
	return (1);
}

int			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file(buf)) == -1)
		return (print_error("get, open returns -1"));
	if ((fstat(file, &st)) == -1)
		return (print_error("put, fstat returns -1"));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
	== MAP_FAILED)
		return (print_error("put, mmap returns -1"));
	if (send_get_server(st, fd, ptr) == -1)
		return (print_error("get, fail to send"));
	ft_putendl("\033[32mSUCCESS: get\033[0m");
	close(file);
	return (1);
}
