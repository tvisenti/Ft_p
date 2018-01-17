/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:42:30 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 15:18:06 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

static int		recv_get_client(int fd, int file, int size_max)
{
	char		*buff;
	int			size;
	int			ret;
	
	ret = 0;
	if (!(buff = malloc(sizeof(char) * size_max)))
		return (-1);
	ft_bzero(buff, size_max);
	while (ret < size_max)
	{
		size = recv(fd, buff + ret, 4096, 0);
		if (size % 4096 != 0)
			break ;
		ret += size;
	}
	write(file, buff, size_max);
	write(file, "\0", 1);
	return (1);
}

int			cmd_get_client(int fd, char *buf)
{
	int			file;
	int			size;

	if ((file = open_file(buf)) == -1)
		return (print_error("get [client], can't open this file"));
	if ((size = get_size_file(fd)) == -1)
		return (print_error("get [client], file doesn't exist"));
	if (recv_get_client(fd, file, size) == -1)
		return (print_error("get [client], recv failed"));
	ft_putendl("\033[32mSUCCESS: get\033[0m");
	ft_putstr("$> ");
	close(file);
	return (1);
}