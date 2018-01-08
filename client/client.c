/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 11:01:14 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/08 11:49:01 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void    usage(char *str)
{
    printf("Usage: %s <addr> <port>\n", str);
    exit(-1);
}

int     create_client(char *addr, int port)
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
    sin.sin_addr.s_addr = inet_addr(addr);
    if (connect(sock, (const struct  sockaddr *)&sin, sizeof(sin)) == -1)
    {
        printf("Connect error\n");
        exit(2);
    }
    return (sock);
}

int     main(int ac, char **av)
{
    int                 port;
    int                 sock;

    if (ac != 3)
        usage(av[0]);
    port = atoi(av[2]);
    sock = create_client(av[1], port);
    write(sock, "Bonjour\n", 8);
    close(sock);
    return (0);
}