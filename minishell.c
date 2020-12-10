/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:30:48 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/09 12:39:19 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void		parse_exec(t_ms *ms)
{
	int		i;

	if (parse_total_cmds(ms))
	{
		clean_stx_err(ms);
		return ;
	}
	if (ms->cmd_tab)
	{
		i = -1;
		while (ms->cmd_tab[++i])
		{
			ms->input = ft_strdup(ms->cmd_tab[i]);
			parse(ms);
			if (ms->cmd_err || (ms->lst_end && !ms->lst_end->end))
			{
				clean_stx_err(ms);
				break ;
			}
			exec_command(ms);
			internal_init(ms);
		}
	}
	init(ms, 2, NULL);
}

void		handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_ret = 1;
		ft_putstr_fd("\n\033[1;31m$minishell$~> \033[0m", 1);
	}
	else if (sig == SIGQUIT)
	{
		if (g_ret == 2)
			ft_putendl_fd("Quit: 3", 2);
		else
			ft_putstr_fd("\b\b  \b\b", 2);
	}
}

int			minishell(char **env, int step)
{
	t_ms	*ms;

	ms = (t_ms*)malloc(sizeof(t_ms));
	if (!step)
		init(ms, 0, env);
	while (1)
	{
		if (ms->status != 130)
			ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		parse_exec(ms);
		g_ret = 0;
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	ac = 0;
	g_ret = 0;
	av = NULL;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	minishell(env, 0);
	return (0);
}
