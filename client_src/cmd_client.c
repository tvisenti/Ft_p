/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:28:00 by tvisenti          #+#    #+#             */
/*   Updated: 2018/01/31 12:09:15 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		check_permissions_client(char *absolute_path)
{
	char	path[UCHAR_MAX];

	getcwd(path, UCHAR_MAX);
	if (ft_strncmp(absolute_path, path, ft_strlen(absolute_path)) != 0)
	{
		chdir(absolute_path);
		return (print_error("lcd, no permissions to access here"));
	}
	return (1);
}

int		cmd_lls(char *arg)
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
		return (print_error("lls, can't access to this dir"));
	while ((file = readdir(dir)))
	{
		name = file->d_name;
		if (ft_strncmp(".", name, 1) != 0)
			ft_putendl(name);
	}
	ft_putendl("\033[32mSUCCESS: lls\033[0m");
	closedir(dir);
	return (1);
}

int		cmd_lcd(char *arg, char *absolute_path)
{
	char	*dir;
	int		ret;

	dir = ft_strdup(arg);
	if (!dir || ft_strlen(dir) == 0)
		return (print_error("lcd, Failed to get arg for cd command"));
	if ((ret = chdir(dir)) == -1)
		return (print_error("lcd, chdir failed"));
	if (check_permissions_client(absolute_path) == -1)
		return (-1);
	ft_putendl("\033[32mSUCCESS: lcd\033[0m");
	free(dir);
	return (1);
}

int		cmd_lpwd(void)
{
	char	path[UCHAR_MAX];

	if (getcwd(path, UCHAR_MAX) == NULL)
		return (print_error("lpwd failed"));
	ft_putendl(path);
	ft_putendl("\033[32mSUCCESS: lpwd\033[0m");
	return (1);
}

int		cmd_lmkdir(char *arg)
{
	if (!arg || ft_strlen(arg) == 0)
		return (print_error("lmkdir failed, no path specified"));
	if (mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
		return (print_error("lmkdir, chdir failed"));
	ft_putendl("\033[32mSUCCESS: lmkdir\033[0m");
	return (1);
}
