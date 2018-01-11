/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 14:41:06 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/11 11:05:14 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../inc/libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
