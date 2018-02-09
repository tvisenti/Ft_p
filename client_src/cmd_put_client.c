/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/09 17:00:45 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static void		send_put_client(struct stat st, int fd, void *ptr)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	if (recv_alert("SEND", fd) < 1)
		return ;
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
	if (recv_alert("SUCCESS", fd) == 1)
		ft_putendl("\033[32mSUCCESS: put\033[0m");
}

void			cmd_put_client(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_rdonly(buf, fd)) == -1)
		return (print_error_get_put("open() client side failed"));
	if (recv_alert("WRONLY_OK", fd) < 1)
		return (print_error_get_put("Can't create the file, already exists"));
	if ((fstat(file, &st)) == -1)
		return (print_error_get_put("fstat() client side failed"));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl("\033[32mSUCCESS: put\033[0m");
		return (print_error_get_put(\
			"Error on mmap(), could be an empty file"));
	}
	ft_putendl_fd("TEST_OK", fd);
	send_put_client(st, fd, ptr);
	close(file);
}
