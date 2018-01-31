/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:26:40 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/31 10:07:31 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** Cree un server et recupere avec protobyname le protocol number avec
** la struct protoend et la fonction getprotobyname("tcp")
*/

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	ft_memset((void *)&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (print_error("bind failed"));
	if (listen(sock, 42) == -1)
		return (print_error("listen failed"));
	return (sock);
}

int		get_cmd(char *str, int fd, char *pwd)
{
	ft_putstr("$> ");
	ft_putendl(str);
	if (ft_strncmp(str, "ls", 2) == 0 && ft_strlen(str) >= 2)
		cmd_ls(fd, &str[3]);
	else if (ft_strncmp(str, "cd ", 3) == 0 && ft_strlen(str) > 3)
		cmd_cd(fd, &str[3], pwd);
	else if (ft_strncmp(str, "get ", 4) == 0 && ft_strlen(str) > 4)
		cmd_get_server(fd, &str[4]);
	else if (ft_strncmp(str, "put ", 4) == 0 && ft_strlen(str) > 4)
		cmd_put_server(fd, &str[4]);
	else if (ft_strcmp(str, "quit") == 0 && ft_strlen(str) == 4)
		return (-1);
	else if (ft_strcmp(str, "pwd") == 0 && ft_strlen(str) == 3)
		cmd_pwd(fd);
	else if (ft_strncmp(str, "mkdir ", 6) == 0 && ft_strlen(str) > 6)
		cmd_mkdir(fd, &str[6]);
	else
		print_fd_err("Command not found", fd);
	return (1);
}

void	handler_serv(int fd)
{
	char	*pwd;
	char	*buf;

	pwd = malloc(sizeof(char) * UCHAR_MAX);
	getcwd(pwd, UCHAR_MAX);
	while (42)
	{
		if (get_next_line(fd, &buf) > 0)
		{
			if (get_cmd(buf, fd, pwd) == -1)
				break ;
		}
		else
			break ;
		free(buf);
	}
	free(pwd);
	close(fd);
}

int		accept_fork(int sock)
{
	pid_t				pid;
	int					sock_client;

	ft_putendl("Waiting a client ...");
	while (42)
	{
		if ((sock_client = accept(sock, (struct sockaddr*)NULL, NULL)))
		{
			if ((pid = fork()) == -1)
				return (print_error("Fork failed"));
			else if (pid == 0)
			{
				ft_putendl("Hello new client!");
				handler_serv(sock_client);
				ft_putendl("Goodbye ex-client!");
				break ;
			}
		}
		else
			return (print_error("Accept failed"));
	}
	close(sock_client);
	return (1);
}

int		main(int ac, char **av)
{
	int				port;
	int				sock;

	if (ac != 2)
	{
		ft_putstr("Usage: ");
		ft_putstr(av[0]);
		ft_putendl(" <port>\n");
		return (-1);
	}
	port = atoi(av[1]);
	if ((sock = create_server(port)) == -1)
		return (-1);
	if ((accept_fork(sock)) == -1)
		return (-1);
	close(sock);
	return (0);
}
