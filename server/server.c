/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:26:40 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/08 11:00:03 by tvisenti         ###   ########.fr       */
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
    printf("Usage: %s <port>\n", str);
    exit(-1);
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
    {
        printf("Bind error");
        exit(-1);
    }
    listen(sock, 42);
    return (sock);
}

int     main(int ac, char **av)
{
    int                 port;
    int                 sock;
    int                 cs;
    struct sockaddr_in  *csin;
    unsigned int        cslen;
    int                 r;
    char                buf[1024];

    if (ac != 2)
        usage(av[0]);
    port = atoi(av[1]);
    sock = create_server(port);
    cs = accept(sock, (struct sockaddr*)&csin, &cslen);
    while ((r = read(cs, buf, 1023)) > 0)
    {
        buf[r] = '\0';
        printf("received %d bytes: \n%s", r, buf);
    }
    close(cs);
    close(sock);

    return (0);
}