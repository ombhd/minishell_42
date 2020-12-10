/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 13:34:09 by yslati            #+#    #+#             */
/*   Updated: 2020/12/10 13:27:17 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			pipe_fds(t_ms *ms)
{
	int			i;

	ms->fds = (int *)malloc((2 * ms->pp_count) * sizeof(int));
	ms->tpid = (pid_t *)malloc(sizeof(pid_t) * (ms->pp_count + 1));
	i = -1;
	while (++i < ms->pp_count)
		if ((pipe(ms->fds + (i * 2)) < 0))
			ft_putstr_fd("minishell: piping error\n", 2);
}

char			*is_path_exe(char **tab, t_ms *ms)
{
	int			i;
	struct stat	stats;
	char		*path;

	i = -1;
	stats.st_mode = 0;
	while (tab[++i])
	{
		path = ft_strjoin(tab[i], "/");
		path = clean_join(path, ms->cmds->cmd);
		if ((stat(path, &stats)) == 0 && (stats.st_mode & X_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

char			*get_exec_path(t_ms *ms)
{
	int			i;
	char		**tab;
	char		*path;

	if ((i = get_env(ms->env, ft_strdup("PATH"))) != -1)
	{
		tab = ft_split(ms->env[i] + 5, ':');
		if ((path = is_path_exe(tab, ms)))
		{
			tab = free_str_table(tab);
			i = 1;
			while (ms->cmds->redir && ms->cmds->next->args[i]
			&& ms->cmds->next->args[i][0] == '-')
				ms->cmds->args = get_arr(ft_strdup(ms->cmds->next->args[i++]),
				&ms->cmds->args, '\0');
			return (path);
		}
		tab = free_str_table(tab);
	}
	else
	{
		cmd_error(ms, F_NOT_FOUND_ERR, NULL, ms->cmds->cmd);
		exit(127);
	}
	return (NULL);
}

void			check_command_help(t_ms *ms)
{
	char		*path;

	path = NULL;
	if (!ft_strncmp(ms->cmds->cmd, "./", 2) || ft_strchr(ms->cmds->cmd, '/'))
	{
		if (execve(ms->cmds->cmd, ms->cmds->args, ms->env) < 0)
			exit(cmd_error_help(ms));
	}
	else if (!is_builtin_sys(ms->cmds->cmd))
	{
		path = get_exec_path(ms);
		(path) ? execve(path, ms->cmds->args, ms->env) : 0;
		free(path);
	}
}

int				check_command(t_ms *ms)
{
	int			ret;

	ret = 1;
	if (!ft_strcmp(ms->cmds->cmd, "cd"))
		ret = ft_cd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "pwd"))
		ret = ft_pwd(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "env"))
		ret = ft_env(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "export"))
		ret = ft_export(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "unset"))
		ret = ft_unset(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "echo"))
		ret = ft_echo(ms);
	else if (!ft_strcmp(ms->cmds->cmd, "exit"))
		ret = ft_exit(ms);
	else
		check_command_help(ms);
	return (ret);
}
