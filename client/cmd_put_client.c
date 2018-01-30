/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 11:57:21 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		open_file_put_client(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = cmd;
	while (*filename == ' ')
		++filename;
	ft_putendl(filename);
	if ((file = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("ERROR_FD", fd);
	else
	{
		ft_putendl("CLIENT_OK dans fd")
		ft_putendl_fd("CLIENT_OK", fd);
	}
	ft_putnbr(file);
	return (file);
}

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

	if ((file = open_file_put_client(buf, fd)) == -1)
		return (print_error_get_put("open() client side failed"));
	if (recv_alert("VERIF_FD", fd) < 1)
		return (print_error_get_put("Can't create the file, already exists"));
	if ((fstat(file, &st)) == -1)
		return (print_error_get_put("fstat() client side failed"));
	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
			== MAP_FAILED)
		return (print_error_get_put("mmap() client side failed"));
	ft_putendl_fd("TEST_OK", fd);
	send_put_client(st, fd, ptr);
	ft_putstr("$> ");
	close(file);
}


	// static int		open_file_put_client(char *cmd, int client)
	// {
	// 	char		*filename;
	// 	int			file;

	// 	filename = cmd;
	// 	while (*filename == ' ')
	// 		++filename;
	// 	if ((file = open(filename, O_RDONLY)) == -1)
	// 		ft_putendl_fd("ERROR_FD", client);
	// 	else
	// 		ft_putendl_fd("SERVER_OK", client);
	// 	return (file);
	// }

	// static void		send_put_client(int fd, struct stat st, void *ptr)
	// {
	// 	char		*size;

	// 	size = ft_itoa(st.st_size);
	// 	ft_putendl_fd(size, fd);
	// 	write(fd, "/0", 1);
	// 	free(size);
	// 	if (recv_alert("SEND", fd) < 1)
	// 		return ;
	// 	send(fd, ptr, st.st_size, 0);
	// 	munmap(ptr, st.st_size);
	// }

	// void		cmd_put_client(int fd, char *buf)
	// {
	// 	int			file;
	// 	struct stat	st;
	// 	void		*ptr;

	// 	ft_putendl("SUIS LA");
	// 	if ((file = open_file_put_client(buf, fd)) == -1)
	// 		return (print_error_get_put("open failed"));
	// 	if (recv_alert("VERIF_FD", fd) < 1)
	// 		return (print_error_get_put("file already exists"));
	// 	if ((fstat(file, &st)) == -1)
	// 		return (print_fd_err("TEST_ERROR", fd));
	// 	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0))
	// 			== MAP_FAILED)
	// 		return (print_fd_err("TEST_ERROR", fd));
	// 	ft_putendl_fd("TEST_OK", fd);
	// 	send_put_client(fd, st, ptr);
	// 	if (recv_alert("SUCCESS", fd) == 1)
	// 		ft_putendl("\033[32mSUCCESS: put\033[0m");
	// 	close(file);
	// 	ft_putstr("$> ");
	// }


// static int		send_put_client(struct stat st, int fd, void *ptr, int file)
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

// int			cmd_put_client(int fd, char *buf)
// {
// 	int			file;
// 	struct stat	st;
// 	void		*ptr;

// 	if ((file = open_file_read(buf, fd)) == -1)
// 		return (print_error("put [client], open returns -1"));
// 	if ((fstat(file, &st)) == -1)
// 		return (print_error("put [client], fstat returns -1"));
// 	if ((ptr = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, file, 0)) 
// 	== MAP_FAILED)
// 		return (print_error("put [client], mmap returns -1"));
// 	if (send_put_client(st, fd, ptr, file) == -1)
// 		return (print_error("put [client], fail to send"));
// 	ft_putendl("\033[32mSUCCESS: put\033[0m");
// 	ft_putstr("$> ");
// 	close(file);
// 	return (1);
// }

