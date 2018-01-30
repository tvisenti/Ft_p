/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:07:12 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/30 11:24:55 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

int		recv_alert(char *str, int fd)
{
	char	*buf;

	buf = NULL;
	if (get_next_line(fd, &buf) > 0)
	{
		ft_putstr("buf: ");
		ft_putstr(buf);
		ft_putstr(" | str: ");
		ft_putendl(str);
		if (ft_strcmp(buf, str) == 0)
			return (1);
	}
	return (-1);
}