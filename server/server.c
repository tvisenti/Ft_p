/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:26:40 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/10 17:51:56 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void    usage(char *str)
{
    printf("Usage: %s <port>\n", str);
    exit (-1);
}

int     print_error(char *str)
{
    printf("Error: %s\n", str);
    return (-1);
}

/*
** Cree un server et recupere avec protobyname le protocol number avec 
** la struct protoend et la fonction getprotobyname("tcp")
*/

int     create_server(int port)
{
    int                 sock;
    struct protoent     *proto;
    struct sockaddr_in  sin;

    proto = getprotobyname("tcp");
    if (!proto)
        return (-1);
    sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock, (const struct  sockaddr *)&sin, sizeof(sin)) == -1)
        return print_error("Bind failed");
    listen(sock, 42);
    return (sock);
}

void     handler_serv(int fd)
{
    int                 r;
    char                buf[1024];

    ft_bzero(buf, 1024);
    while (42)
    {
        if ((r = read(fd, buf, 1024)) > 0)
        {
            printf("Buf: %s\n", buf);
            printf("----------\n");
            if (ft_strncmp(buf, "ls", 2) == 0 && ft_strlen(buf) >= 2)
                cmd_ls(fd, ft_strsub(buf, 3, ft_strlen(buf)));
            else if (ft_strncmp(buf, "cd", 2) == 0 && ft_strlen(buf) > 3 && buf[2] == ' ')
                cmd_cd(fd, buf);
            else if (ft_strcmp(buf, "quit") == 0 && ft_strlen(buf) == 4)
                return ;
            else if (ft_strcmp(buf, "pwd") == 0 && ft_strlen(buf) == 3)
                cmd_pwd(fd);
            else if (ft_strncmp(buf, "mkdir", 5) == 0 && ft_strlen(buf) > 6 && buf[5] == ' ')
                cmd_mkdir(fd, buf);
            else
                printf("[%s] is a unknown command.\n", buf);
            ft_bzero(buf, ft_strlen(buf));
            printf("----------\n");
        }
    }
}

int     accept_fork(unsigned int sock)
{
    int                 cs;
    struct sockaddr_in  *csin;
    unsigned int        cslen;    
    pid_t               pid;
    int                 sock_client;

    while (42)
    {
        if ((sock_client = accept(sock, (struct sockaddr*)&csin, &cslen)))
        {
            if ((pid = fork()) == -1)
                return print_error("Fork failed");
            else if (pid == 0)
            {
                handler_serv(sock_client);
                close(sock_client);
                break ;
            }
        }
        else
            return print_error("Accept failed");
    }
    close(cs);
    return (1);
}

int     main(int ac, char **av)
{
    int                 port;
    unsigned int        sock;


    if (ac != 2)
        usage(av[0]);
    port = atoi(av[1]);
    if ((sock = create_server(port)) == -1)
        return (-1);
    if ((accept_fork(sock)) == -1)
        return (-1);
    close(sock);
    return (0);
}