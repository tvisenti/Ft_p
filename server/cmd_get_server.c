/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 09:43:50 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/29 18:20:46 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		open_file_get_server(char *cmd, int client)
{
	char		*filename;
	int			file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("ERROR_FD", client);
	else
		ft_putendl_fd("SERVER_OK", client);
	return (file);
}

static void		send_get_server(int fd, struct stat st, void *ptr)
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
		ft_putendl_fd("\033[32mSUCCESS: get\033[0m", fd);
}

void			cmd_get_server(int fd, char *buf)
{
	int			file;
	struct stat	st;
	void		*ptr;

	if ((file = open_file_get_server(buf, fd)) == -1)
		return ;
	if (recv_alert("VERIF_FD", fd) < 1)
		return ;
	if ((fstat(file, &st)) == -1)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return ;
	}
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
	{
		ft_putendl_fd("TEST_ERROR", fd);
		return ;
	}
	ft_putendl_fd("TEST_OK", fd);
	send_get_server(fd, st, ptr);
}


// static int		send_get_server(struct stat st, int fd, void *ptr, int file)
// {
// 	char		*size;

// 	size = ft_itoa(st.st_size);
// 	ft_putendl_fd(size, fd);
// 	write(fd, "\0", 1);
// 	free(size);
// 	if (send(fd, ptr, st.st_size, 0) == -1)
// 		return (-1);
// 	send(fd, "\0", 1, 0);
// 	munmap(ptr, st.st_size);
// 	close(file);
// 	return (1);
// }

// int			cmd_get_server(int fd, char *buf)
// {
// 	int			file;
// 	struct stat	st;
// 	void		*ptr;

// 	if ((file = open_file_read(buf)) == -1)
// 		return (print_fd_err_int("get [server], open returns -1", fd));
// 	if ((fstat(file, &st)) == -1)
// 		return (print_fd_err_int("get [server], fstat returns -1", fd));
// 	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
// 	== MAP_FAILED)
// 		return (print_fd_err_int("get [server], mmap returns -1", fd));
// 	if (send_get_server(st, fd, ptr, file) == -1)
// 		return (print_fd_err_int("get [server], fail to send", fd));
// 	ft_putendl("\033[32mSUCCESS: get [server]\033[0m");
// 	ft_putstr("$> ");
// 	close(file);
// 	return (1);
// }
