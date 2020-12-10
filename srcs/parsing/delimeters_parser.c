/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimeters_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 20:53:49 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/10 10:52:02 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		parse_scolon(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		parse_pipe(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	ms->pp_count++;
	ms->is_pipe = 1;
}

void		parse_trunc_rdr(t_ms *ms, int b, int *i, char *s)
{
	char *tmp;

	ms->redir = TRUNC;
	if (s[*i + 1] == '>')
		ms->redir = APPEND;
	tmp = ft_strldup(s + b, *i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
	*i += (s[*i + 1] == '>');
}

void		parse_read_rdr(t_ms *ms, int b, int i, char *s)
{
	char *tmp;

	ms->redir = READ;
	tmp = ft_strldup(s + b, i - b);
	if (!(ms->tab = parse_split(tmp, ' ', ms)))
		errex(ms, SPLT_ERR);
	free(tmp);
}

void		new_cmd(t_ms *ms, char del, char **tab)
{
	t_cmd	*c;

	if (!(c = (t_cmd*)malloc(sizeof(t_cmd))))
		return ;
	c->next = NULL;
	c->cmd = ft_strdup(tab[0]);
	c->args = rm_empty_str(dup_str_tab(tab, '\0'));
	c->redir = ms->redir;
	if (ms->cmds != NULL)
		c->start = (ms->cmds->end == 1) ? 1 : 0;
	else
		c->start = 1;
	c->end = (del == S_COLON) ? 1 : 0;
	c->is_err = ms->cmd_err != 0;
	c->is_pipe = ms->is_pipe;
	if (ms->cmds)
		ms->cmds->next = c;
	c->prev = ms->cmds;
	ms->cmds = c;
}
