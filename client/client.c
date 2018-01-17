/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 11:01:14 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/17 14:28:19 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("Connect error\n");
		exit(2);
	}
	return (sock);
}

void	read_client(int fd, char *buf)
{
	int	r;

	while ((r = read(fd, buf, 1)) > 0 && buf[0] != '\0')
	{
		buf[r] = '\0';
		write(1, buf, r);
	}
	write(1, "$> ", 3);
}

int		get_size(int fd)
{
	int			size;
	char		*line;

	size = 0;
	if (get_next_line(fd, &line) == 1)
	{
		size = ft_atoi(line);
		if (size < 1)
			return (-1);
	}
	else
		return (-1);
	return (size);
}

void	clear_buf(int fd, char *buf)
{
	int			size_max;
	int			size;
	int			ret;

	ret = 0;
	size_max = get_size(fd);
	if (size_max < 0)
		ft_putendl("ERROR");
	while (ret < size_max)
	{
		size = read(fd, buf + ret, 4096);
		if (size % 4096 != 0)
			break ;
		ret += size;
	}
	ft_putstr("$> ");
}

void	wait_user_input(int fd)
{
	int		r;
	char	*buf;

	write(1, "$> ", 3);
	while ((r = get_next_line(0, &buf)) > 0)
	{
		ft_putendl_fd(buf, fd);
		write(fd, "\0", 1);
		if (ft_strcmp(buf, "quit") == 0)
			return ;
		else if (ft_strncmp(buf, "get ", 4) == 0 && ft_strlen(buf) > 4)
		{
			if (cmd_get_client(fd, &buf[3]) == -1)
				clear_buf(fd, buf);
		}
		else if (ft_strncmp(buf, "put ", 4) == 0 && ft_strlen(buf) > 4)
			cmd_put_client(fd, &buf[3]);
		else
			read_client(fd, ft_strdup(buf));
		ft_bzero(buf, ft_strlen(buf));
	}
}

int		main(int ac, char **av)
{
	int	port;
	int	sock;

	if (ac != 3)
		usage(av[0]);
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	wait_user_input(sock);
	close(sock);
	return (0);
}
