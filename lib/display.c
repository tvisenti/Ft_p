/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:10:41 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/12 15:11:43 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

void    usage(char *str)
{
	printf("Usage: %s <addr> <port>\n", str);
	exit(-1);
}

void	print_fd_err(char *str, int fd)
{
    ft_putendl(str);
	ft_putendl_fd(str, fd);
	write(fd, "\0", 1);
	return ;
}

void	print_fd(char *str, int fd)
{
	ft_putendl(str);
	ft_putendl_fd(str, fd);
}

int     print_error(char *str)
{
    printf("Error: %s\n", str);
    return (-1);
}