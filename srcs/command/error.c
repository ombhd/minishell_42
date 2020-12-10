/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:05:17 by yslati            #+#    #+#             */
/*   Updated: 2020/12/09 12:04:35 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				check_permission(char *path, int mode)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) < 0)
		return (0);
	if (mode == 1)
		return (file_stat.st_mode & S_IXUSR ? 1 : 0);
	else if (mode == 2)
		return (file_stat.st_mode & S_IWUSR ? 1 : 0);
	else if (mode == 3)
		return (file_stat.st_mode & S_IRUSR ? 1 : 0);
	return (0);
}

int				cmd_error_help(t_ms *ms)
{
	struct stat	stats;
	int			ret;

	ret = 0;
	stats.st_mode = 0;
	if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
	{
		stat(ms->cmds->cmd, &stats);
		if (stats.st_mode == 16877 && (ret = 126))
			cmd_error(ms, IS_DIRECTORY_ERR, NULL, ms->cmds->cmd);
		else if (!check_permission(ms->cmds->cmd, 1) &&
		check_permission(ms->cmds->cmd, 3) && (ret = 126))
			cmd_error(ms, PERMISSION_ERR, NULL, ms->cmds->cmd);
		else if (ft_strchr(ms->cmds->cmd, '/'))
			cmd_error(ms, F_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
		else
			cmd_error(ms, CMD_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
	}
	return ((!ret) ? 127 : ret);
}

int				cmd_error(t_ms *ms, int err, char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	(err == OLDPWD_ERR) ? ft_putendl_fd("OLDPWD not set", 2) : 0;
	if (arg)
	{
		(err == NOT_VALID_ERR) ? ft_putchar_fd('`', 2) : 0;
		ft_putstr_fd(arg, 2);
		if (err == NOT_VALID_ERR)
			ft_putendl_fd("': not a valid identifier", 2);
		else if (err == F_NOT_FOUND_ERR)
			ft_putendl_fd(": No such file or directory", 2);
		else if (err == HOME_NOT_SET_ERR)
			ft_putendl_fd(": HOME not set", 2);
		else if (err == CMD_NOT_FOUND_ERR)
			ft_putstr_fd(": command not found\n", 2);
		else if (err == IS_DIRECTORY_ERR)
			ft_putstr_fd(": is a directory\n", 2);
		else if (err == PERMISSION_ERR)
			ft_putstr_fd(": Permission denied\n", 2);
	}
	return ((ms->status = 1) && 1);
}
