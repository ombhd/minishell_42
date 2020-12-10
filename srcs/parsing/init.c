/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 12:03:01 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/10 13:26:19 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parser(t_parser *p)
{
	p->i = 0;
	p->j = 0;
	p->m = 0;
	p->quote_ig = 0;
	p->slash_ig = 0;
	p->l = 0;
}

void	init_zero(t_ms *ms, char **env)
{
	int i;

	ms->status = 0;
	ms->input = NULL;
	ms->env = dup_str_tab(env, '\0');
	if ((i = check_exist(ms->env, "OLDPWD")) != -1)
	{
		free(ms->env[i]);
		ms->env[i] = ft_strdup("OLDPWD");
	}
	else
		ms->env = add_to_arr(ft_strdup("OLDPWD"), &ms->env, '\0');
	ms->p_env = dup_str_tab(ms->env, 'p');
	ms->pwd = getcwd(NULL, 0);
	ms->old_pwd = NULL;
	ms->cmd_tab = NULL;
	ms->tab = NULL;
	ms->cmds = NULL;
	ms->fds = NULL;
	ms->tpid = NULL;
	ms->ret_status = 0;
}

void	internal_init(t_ms *ms)
{
	ms->err = 0;
	ms->cmd_err = 0;
	ms->redir = 0;
	ms->pp_count = 0;
	ms->input = ft_free(ms->input);
	ms->fds = ft_free(ms->fds);
	ms->tpid = ft_free(ms->tpid);
	free_cmds(ms);
}

void	init(t_ms *ms, char step, char **env)
{
	ms->err = 0;
	ms->cmd_err = 0;
	ms->redir = 0;
	ms->ctrl = 0;
	ms->pp_count = 0;
	ms->fds = NULL;
	ms->tpid = NULL;
	if (!step)
		init_zero(ms, env);
	if (step == 2)
	{
		if (ms->tab)
			ms->tab = free_str_table(ms->tab);
		if (ms->cmd_tab)
			ms->cmd_tab = free_str_table(ms->cmd_tab);
		free_cmds(ms);
	}
}
