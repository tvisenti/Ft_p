/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:10:41 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 11:12:18 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

void	usage(char *str)
{
	ft_putstr("Usage: ");
	ft_putstr(str);
	ft_putendl(" <addr> <port>\n");
	exit(-1);
}

void		print_error_get_put(char *str)
{
	ft_putstr("\033[31mERROR: ");
	ft_putstr(str);
	ft_putendl("\033[0m");
	ft_putstr("$> ");
	return ;
}

int		print_fd_err_int(char *str, int fd)
{
	ft_putstr("\033[31mERROR: ");
	ft_putstr(str);
	ft_putendl("\033[0m");

	ft_putstr_fd("\033[31mERROR: ", fd);
	ft_putstr_fd(str, fd);
	ft_putendl_fd("\033[0m", fd);
	write(fd, "\0", 1);
	return (-1) ;
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

int		print_error(char *str)
{
	ft_putstr("\033[31mERROR: ");
	ft_putstr(str);
	ft_putendl("\033[0m");
	ft_putchar('\0');
	return (-1);
}
