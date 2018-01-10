/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:24:35 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/10 11:57:07 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		cmd_ls(int fd)
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		sb;

	dir = opendir(".");
	file = NULL;
	if (stat(".", &sb) == -1 || dir == NULL)
		return print_error("Error stat for ls");
	while ((file = readdir(dir)) != NULL)
	{
		if (file->d_name[0] != '.')
		{
			printf("%s\n", file->d_name);
			ft_putstr_fd(file->d_name, fd);
			ft_putstr_fd("\n", fd);
		}
	}
	closedir(dir);
	return (1);
}

int		cmd_cd(char *arg)
{
	char	*dir;
	int		ret;

	dir = ft_strtrim(ft_strsub(arg, 3, ft_strlen(arg)));
	if (!dir || ft_strlen(dir) == 0)
		return print_error("Failed to get arg for cd command.");
	printf("Dir: %s\n", dir);
	if ((ret = chdir(dir)) == -1)
	{
		free(dir);
		return print_error("Chdir failed");
	}
	printf("Chdir sucess\n");
	free(dir);
	return (1);
}

int		cmd_pwd()
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return print_error("Getcwd failed");
	printf("Getcwd sucess\n");
	printf("%s\n", path);
	return (1);
}

int		cmd_mkdir(char *arg)
{
	char	*dir;
	int		ret;

	dir = ft_strtrim(ft_strsub(arg, 6, ft_strlen(arg)));
	if (!dir || ft_strlen(dir) == 0)
		return print_error("Failed to get arg for cd command.");
	printf("New dir: %s\n", dir);
	if ((ret = mkdir(dir, 0777)) == -1)
	{
		free(dir);
		return print_error("Chdir failed");
	}
	printf("Mkdir sucess\n");
	free(dir);
	return (1);
}