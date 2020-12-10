/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:23:08 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/10 11:54:56 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_stx_err(t_ms *ms)
{
	ft_putendl_fd("minishell: syntax error", 1);
	if (ms->cmd_tab)
		ms->cmd_tab = free_str_table(ms->cmd_tab);
	ms->status = 258;
	ms->input = ft_free(ms->input);
}

void	*ft_free(void *mem_ptr)
{
	free(mem_ptr);
	return (NULL);
}

void	free_cmds(t_ms *ms)
{
	t_cmd *c;
	t_cmd *tmp;

	c = ms->cmds;
	while (c)
	{
		free(c->cmd);
		c->cmd = NULL;
		c->args = free_str_table(c->args);
		tmp = c;
		c = c->next;
		tmp = ft_free(tmp);
	}
	ms->cmds = NULL;
}

char	*clean_join(char *s1, char *s2)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	return (s1);
}

void	errex(t_ms *ms, int err)
{
	if (err == RDIN_ERR)
		ft_putendl_fd("minishell: reading input error", 1);
	else if (err == SPLT_ERR)
		ft_putendl_fd("minishell: splitting input error", 1);
	ft_exit(ms);
}
