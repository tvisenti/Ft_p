/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/12 17:12:42 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

int				send_error(int client, char *msg)
{
	ft_putendl_fd(msg, client);
	return (-1);
}

static int		open_file(char *cmd, int client)
{
	char		*filename;
	int			file;

	filename = &cmd[3];
	while (*filename == ' ')
		++filename;
	if ((file = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("ERROR_FD", client);
	else
		ft_putendl_fd("SERVER_OK", client);
	return (file);
}

static void		run_get(int fd, struct stat st, void *ptr)
{
	char		*size;

	size = ft_itoa(st.st_size);
	ft_putendl_fd(size, fd);
	free(size);
	// if (alert_message("SEND", fd) < 1)
	// 	return ;
	send(fd, ptr, st.st_size, 0);
	munmap(ptr, st.st_size);
}

void			cmd_get(int	fd, char *buf)
{
	void		*ptr;
	int			file;
	struct stat	st;

	if ((file = open_file(buf, fd)) == -1)
		return ;
	// if (alert_message("VERIF_FD", fd) < 1)
	// 	return ;
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
	run_get(fd, st, ptr);
	close(file);
	// if (alert_message("SUCCESS", fd) == 1)
	// 	ft_putendl_fd("\033[32mSUCCESS\033[0m", fd);
}