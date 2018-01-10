/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:24:35 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/10 17:47:25 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		cmd_ls(int fd, char *arg)
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		sb;

	if (ft_strlen(arg) == 0 || !arg)
		arg = ft_strdup(".");
	dir = opendir(arg);
	file = NULL;
	if (stat(arg, &sb) == -1 || dir == NULL)
	{
		ft_putendl_fd("ERROR | cmd: ls -> can't access to this dir", fd);
		return print_error("Can't access to this dir");
	}
	ft_putendl_fd("SUCCESS | cmd: ls", fd);
	printf("SUCCESS | cmd: ls\n");	
	while ((file = readdir(dir)) != NULL)
	{
		if (file->d_name[0] != '.')
		{
			printf("%s\n", file->d_name);
			ft_putendl_fd(file->d_name, fd);
		}
	}
	closedir(dir);
	return (1);
}

int		cmd_cd(int fd, char *arg)
{
	char	*dir;
	int		ret;

	dir = ft_strtrim(ft_strsub(arg, 3, ft_strlen(arg)));
	if (!dir || ft_strlen(dir) == 0)
	{
		ft_putendl_fd("ERROR | cmd: cd -> failed to get arg for cd command", fd);
		return print_error("Failed to get arg for cd command.");
	}
	printf("Dir: %s\n", dir);
	if ((ret = chdir(dir)) == -1)
	{
		free(dir);
		ft_putendl_fd("ERROR | cmd: cd -> chdir failed", fd);	
		return print_error("Chdir failed");
	}
	printf("SUCCESS | cmd: cd\n");
	ft_putendl_fd("SUCCESS | cmd: cd", fd);
	free(dir);
	return (1);
}

int		cmd_pwd(int fd)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
	{
		ft_putendl_fd("ERROR | cmd: pwd -> getcwd failed", fd);
		return print_error("Getcwd failed");
	}
	printf("SUCCESS | cmd: pwd\n");
	ft_putendl_fd("SUCCESS | cmd: pwd", fd);
	printf("%s\n", path);
	return (1);
}

int		cmd_mkdir(int fd, char *arg)
{
	char	*dir;
	int		ret;

	dir = ft_strtrim(ft_strsub(arg, 6, ft_strlen(arg)));
	if (!dir || ft_strlen(dir) == 0)
	{
		ft_putendl_fd("ERROR | cmd: mkdir -> not a valid format", fd);
		return print_error("Not a valid format");
	}
	printf("New dir: %s\n", dir);
	if ((ret = mkdir(dir, 0777)) == -1)
	{
		free(dir);
		ft_putendl_fd("ERROR | cmd: mkdir -> chdir failed", fd);
		return print_error("Chdir failed");
	}
	printf("SUCCESS | cmd: mkdir\n");
	ft_putendl_fd("SUCCESS | cmd: mkdir", fd);
	free(dir);
	return (1);
}