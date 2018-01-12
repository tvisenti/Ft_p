/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:24:35 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/12 12:53:38 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		check_permissions(int fd, char *absolute_path, char *arg, int ls)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0 ||
	((ls == 1) && (ft_strncmp(arg, "..", 4) == 0)) ||
	((ls == 1) && (arg[0] == '/') &&
	(ft_strncmp(arg, absolute_path, ft_strlen(absolute_path)) != 0)))
	{
		if (ls == 0)
		{
			chdir(absolute_path);
			print_fd_err("\033[31mERROR: cd, no permissions
			to access here\033[0m", fd);
		}
		else
			print_fd_err("\033[31mERROR: ls, no permissions
			to access here\033[0m", fd);
		return (0);
	}
	return (1);
}

void	cmd_ls(int fd, char *arg, char *absolute_path)
{
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	if (ft_strlen(arg) == 0 || !arg)
		arg = ft_strdup(".");
	if (!(dir = opendir(arg)))
		return print_fd_err("\033[31mERROR: ls, can't access to
		this dir\033[0m", fd);
	if (check_permissions(fd, absolute_path, arg, 1) == 0)
		return ;
	while ((file = readdir(dir)))
	{
		name = file->d_name;
		if (ft_strncmp(".", name, 1) != 0)
			print_fd(name, fd);
	}
	print_fd("\033[32mSUCCESS: ls\033[0m", fd);
	write(fd, "\0", 1);
	closedir(dir);
}

void	cmd_cd(int fd, char *arg, char *absolute_path)
{
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	if (!dir || ft_strlen(dir) == 0)
		return print_fd_err("\033[31mERROR: cd, Failed to get arg for
		cd command\033[0m", fd);
	if ((ret = chdir(dir)) == -1)
		return print_fd_err("\033[31mERROR: cd, chdir failed\033[0m", fd);
	if (check_permissions(fd, absolute_path, arg, 0) == 0)
		return ;
	print_fd("\033[32mSUCCESS: cd\033[0m", fd);
	write(fd, "\0", 1);
	free(dir);
}

void	cmd_pwd(int fd)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return print_fd_err("\033[31mERROR: pwd failed\033[0m", fd);
	print_fd(path, fd);
	print_fd("\033[32mSUCCESS: pwd", fd);
	write(fd, "\0", 1);
}

void	cmd_mkdir(int fd, char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
		return print_fd_err("\033[31mERROR: mkdir failed, no path
		specified\033[0m", fd);
	ft_putstr("New dir: ");
	ft_putendl(arg);
	if (mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		print_fd_err("\033[31mERROR: mkdir, chdir failed\033[0m", fd);
	print_fd("\033[32mSUCCESS: mkdir\033[0m", fd);
	write(fd, "\0", 1);
}