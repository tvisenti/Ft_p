/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 13:07:12 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/29 15:13:38 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_p.h"

int		open_file(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(cmd);
	file = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (file == -1)
		ft_putendl_fd("OPEN_NO", fd);
	else
		ft_putendl_fd("OPEN_OK", fd);
	free(filename);
	return (file);
}

int		open_file_read(char *cmd, int fd)
{
	char		*filename;
	int			file;

	filename = ft_strtrim(cmd);
	if ((file = open(filename, O_RDONLY)) == -1)
		ft_putendl_fd("OPEN_NO", fd);
	else
		ft_putendl_fd("OPEN_OK", fd);
	free(filename);
	return (file);
}

int		recv_alert(char *str, int fd)
{
	char	*buf;

	buf = NULL;
	if (get_next_line(fd, &buf) > 0)
	{
		if (ft_strcmp(buf, str) == 0)
			return (1);
	}
	return (-1);
}

int		get_size_file(int fd)
{
	int			size;
	char		*line;

	size = 0;
	if (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		size = ft_atoi(line);
		if (size < 1)
		{
			free(line);
			ft_putendl_fd("-1", fd);
			return (-1);
		}
		free(line);
	}
	else
		return (-1);
	return (size);
}