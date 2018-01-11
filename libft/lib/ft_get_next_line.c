/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:47:29 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/11 11:47:42 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int			rootcpy(char **occ, char *root)
{
	if (*occ)
	{
		**occ = '\0';
		*occ += 1;
		ft_strcpy(root, *occ);
		return (1);
	}
	else
		return (0);
}

static char			*freeline(char **line, int *ret)
{
	char			*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(*line) + *ret + 1));
	if (!str)
		return (NULL);
	str = ft_strcpy(str, *line);
	free(*line);
	return (str);
}

int					ft_get_next_line(int const fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static char		root[BUFF_SIZE] = "";
	char			*occ;

	if (!line || !(*line = (char *)malloc(sizeof(char *) *
		(BUFF_SIZE + ft_strlen(root) + 1))) || BUFF_SIZE <= 0 || fd < 0)
		return (-1);
	*line = ft_strcpy(*line, root);
	while (!(occ = ft_strchr(*line, '\n'))
		&& ((ret = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[ret] = '\0';
		if ((*line = freeline(line, &ret)) == NULL)
			return (-1);
		ft_strcat(*line, buf);
	}
	occ = ft_strchr(*line, '\n');
	ft_bzero(root, BUFF_SIZE);
	if (rootcpy(&occ, root) == 1)
		return (1);
	if (ft_strlen(*line) != 0)
		return (1);
	return (ret == 0 ? 0 : -1);
}
