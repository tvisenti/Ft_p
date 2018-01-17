/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 14:37:35 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		send_put_client(struct stat st, int fd, void *ptr, int file)
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

int			cmd_put_client(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_read(buf)) == -1)
		return (print_error("put, open returns -1"));
	if ((fstat(file, &st)) == -1)
		return (print_error("put, fstat returns -1"));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0)) 
	== MAP_FAILED)
		return (print_error("put, mmap returns -1"));
	if (send_put_client(st, fd, ptr, file) == -1)
		return (print_error("get, fail to send"));
	ft_putendl("\033[32mSUCCESS: put\033[0m");
	ft_putstr("$> ");
	return (1);
}

