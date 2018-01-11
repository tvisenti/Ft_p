/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:24:35 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/11 17:42:40 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	cmd_ls(int fd, char *arg)
{
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	ft_putendl(arg);
	if (ft_strlen(arg) == 0 || !arg)
		arg = ft_strdup(".");
	if (!(dir = opendir(arg)))
		return print_fd_err("-> ERROR: Can't access to this dir", fd);
	while ((file = readdir(dir)))
	{
		name = file->d_name;
		if (ft_strncmp(".", name, 1) != 0)
			print_fd(name, fd);
	}
	print_fd("-> SUCCESS: ls", fd);
	write(fd, "\0", 1);
	closedir(dir);
	free(arg);
}

void	cmd_cd(int fd, char *arg, char *absolute_path)
{
	char	path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	if (!dir || ft_strlen(dir) == 0)
		return print_fd_err("-> ERROR: Failed to get arg for cd command", fd);
	if ((ret = chdir(dir)) == -1)
		return print_fd_err("-> ERROR: chdir failed", fd);
	getcwd(path, UCHAR_MAX);
	ft_putendl(path);
	ft_putendl(absolute_path);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(absolute_path);
		return print_fd_err("-> ERROR: No permission to access here", fd);
	}
	print_fd("-> SUCCESS: cd", fd);
	write(fd, "\0", 1);
	free(arg);
}

void	cmd_pwd(int fd)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return print_fd_err("-> ERROR: pwd failed", fd);
	print_fd(path, fd);
	print_fd("-> SUCCESS: pwd", fd);
	write(fd, "\0", 1);
}

void	cmd_mkdir(int fd, char *arg)
{
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	if (!dir || ft_strlen(dir) == 0)
	{

		ft_putendl_fd("ERROR | cmd: mkdir -> not a valid format", fd);
		print_error("Not a valid format");
	}
	printf("New dir: %s\n", dir);
	if ((ret = mkdir(dir, 0777)) == -1)
	{
		free(dir);
		ft_putendl_fd("ERROR | cmd: mkdir -> chdir failed", fd);
		print_error("Chdir failed");
	}
	printf("SUCCESS | cmd: mkdir\n");
	ft_putendl_fd("SUCCESS | cmd: mkdir", fd);
	free(dir);
}