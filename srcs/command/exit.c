/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:36:36 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/09 13:13:32 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				is_set(char *target, char *set)
{
	int			i;
	int			j;
	int			b;

	if (!target || !*target || !set)
		return (0);
	j = -1;
	while (target[++j])
	{
		b = 0;
		i = -1;
		while (set[++i])
			if (target[j] == set[i])
				b = 1;
		if (!b)
			return (0);
	}
	return (1);
}

int				nbrlen(long n)
{
	int l;

	l = 1;
	while (n / 10)
	{
		n /= 10;
		l++;
	}
	return (l);
}

void			exit_analyse(t_ms *ms, int *b)
{
	char	*tmp;
	char	sign;

	tmp = ms->cmds->args[1];
	sign = 0;
	if ((*tmp == '+' || *tmp == '-') && (sign = 1))
		tmp++;
	if (!is_set(tmp, "0123456789") || (int)ft_strlen(ms->cmds->args[1]) !=
									sign + nbrlen(ft_atoli(ms->cmds->args[1])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(ms->cmds->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ms->ret_status = 255;
	}
	else if (is_set(tmp, "0123456789"))
	{
		if (ms->tab[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			*b = 0;
		}
		else
			ms->ret_status = ft_atoli(ms->cmds->args[1]);
	}
}

void			free_parsing_struct(t_ms *ms)
{
	ms->env = free_str_table(ms->env);
	ms->p_env = free_str_table(ms->p_env);
	ms->tab = free_str_table(ms->tab);
	ms->cmd_tab = free_str_table(ms->cmd_tab);
	free_cmds(ms);
	free(ms->pwd);
	free(ms->old_pwd);
	ms->input = ft_free(ms->input);
	ms->fds = ft_free(ms->fds);
	ms->tpid = ft_free(ms->tpid);
	free(ms);
}

int				ft_exit(t_ms *ms)
{
	int			b;

	if ((ms->cmds && ms->cmds->start) || !ms->cmds)
		ft_putendl_fd("exit", 1);
	if (!ms->ctrl)
	{
		b = 1;
		if (ms->cmds->args[1])
			exit_analyse(ms, &b);
		if (!b && (ms->status = 1))
			return (1);
	}
	b = ms->ctrl == CTRL_D ? 0 : (int)ms->ret_status;
	if ((ms->cmds && ms->cmds->start) || !ms->cmds)
		free_parsing_struct(ms);
	exit(b);
}
