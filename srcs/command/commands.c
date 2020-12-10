/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 09:56:00 by yslati            #+#    #+#             */
/*   Updated: 2020/12/09 11:38:48 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_builtin_sys(char *cmds)
{
	return (!(ft_strcmp(cmds, "env") && ft_strcmp(cmds, "cd") &&
		ft_strcmp(cmds, "pwd") && ft_strcmp(cmds, "export") &&
		ft_strcmp(cmds, "unset") && ft_strcmp(cmds, "echo") &&
		ft_strcmp(cmds, "exit")));
}

t_ms			*exucte_help(t_ms *ms)
{
	while (ms && ms->cmds->redir)
	{
		if (!ms->cmds->next)
			break ;
		ms->cmds = ms->cmds->next;
	}
	return (ms);
}

void			exucte_cmd(t_ms *ms)
{
	while (ms->cmds)
	{
		if ((ms->cmds->start == 0 && ms->cmds->prev->redir)
			|| (ms->cmds->start && is_builtin_sys(ms->cmds->cmd)
			&& (!ms->cmds->redir && !ms->pp_count)))
			break ;
		ms->pid = run_child(ms, 0);
		ms = exucte_help(ms);
		if (ms->pid < 0)
		{
			ft_putstr_fd("minishell: forking error\n", 2);
			exit(0);
		}
		if (ms->cmds->end)
			break ;
		else
			ms->cmds = ms->cmds->next;
		ms->j += 2;
	}
}

void			manage_cmd(t_ms *ms, int is_built_in)
{
	int			st;
	int			i;

	restore_fds(ms->backup);
	i = 0;
	while (ms->pp_count && i < 2 * ms->pp_count)
		close(ms->fds[i++]);
	if (is_built_in)
		return ;
	st = wait_child(ms);
	if (st == 2 || st == 3)
		ms->status = st + 128;
	else
		ms->status = (st >> 8) & 255;
}

void			exec_command(t_ms *ms)
{
	int			i;

	g_ret = !g_ret ? 2 : g_ret;
	if (ms->pp_count)
		pipe_fds(ms);
	i = 0;
	ms->j = 0;
	save_fds(ms->backup);
	if ((ms->cmds->next && !ms->cmds->end) ||
	!is_builtin_sys(ms->cmds->cmd))
		exucte_cmd(ms);
	if (is_builtin_sys(ms->cmds->cmd) && !ms->pp_count)
	{
		i = 1;
		if (!ms->cmds->redir)
			check_command(ms);
	}
	manage_cmd(ms, i);
	ms->cmds = ms->head;
}
