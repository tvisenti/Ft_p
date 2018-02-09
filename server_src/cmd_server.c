/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:24:35 by tvisenti          #+#    #+#             */
/*   Updated: 2018/02/09 10:33:57 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			check_permissions_server(int fd, char *absolute_path,
	char *cur_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(cur_path);
		print_fd_err("cd, no permissions to access here", fd);
		return (0);
	}
	return (1);
}

void		cmd_ls(int fd, char *arg)
{
	char			*open;
	DIR				*dir;
	struct dirent	*file;
	char			*name;

	open = ft_strdup(arg);
	if (ft_strlen(arg) == 0 || !arg || arg[0] == '\n' || arg[0] == '\0')
	{
		free(open);
		open = ft_strdup(".");
	}
	if (!(dir = opendir(open)))
	{
		return (print_fd_err("ls, can't access to this dir", fd));
	}
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

void		cmd_cd(int fd, char *arg, char *absolute_path)
{
	char	cur_path[UCHAR_MAX];
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	getcwd(cur_path, UCHAR_MAX);
	if (!dir || ft_strlen(dir) == 0)
		return (print_fd_err("cd, Failed to get arg for cd command", fd));
	if ((ret = chdir(dir)) == -1)
		return (print_fd_err("cd, chdir failed", fd));
	if (check_permissions_server(fd, absolute_path, cur_path) == 0)
		return ;
	print_fd("\033[32mSUCCESS: cd\033[0m", fd);
	write(fd, "\0", 1);
	free(dir);
}

void		cmd_pwd(int fd)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return (print_fd_err("pwd failed", fd));
	print_fd(path, fd);
	print_fd("\033[32mSUCCESS: pwd\033[0m", fd);
	write(fd, "\0", 1);
}

void		cmd_mkdir(int fd, char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
	{
		return (print_fd_err("mkdir failed, no path specified", fd));
	}
	ft_putstr("New dir: ");
	ft_putendl(arg);
	if (mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		print_fd_err("mkdir, chdir failed", fd);
	print_fd("\033[32mSUCCESS: mkdir\033[0m", fd);
	write(fd, "\0", 1);
}
