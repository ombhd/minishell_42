/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2021/02/23 13:03:04 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			make_cmd(t_ms *ms, int b, int *i, char *s)
{
	ms->is_pipe = 0;
	if (s[*i] == S_COLON)
		parse_scolon(ms, b, *i, ms->input);
	else if (s[*i] == PIPE)
		parse_pipe(ms, b, *i, ms->input);
	else if (s[*i] == TRUNC)
		parse_trunc_rdr(ms, b, i, ms->input);
	else if (s[*i] == READ)
		parse_read_rdr(ms, b, *i, ms->input);
	if (ms->tab[0])
	{
		ms->cmd_err = ms->tab[0][0] == '\0';
		new_cmd(ms, s[*i], ms->tab);
	}
	ms->tab = free_str_table(ms->tab);
	ms->redir = 0;
	ms->cmd_err = 0;
	return (*i + 1);
}

t_cmd		*get_head(t_cmd *cmds, char *err)
{
	if (cmds && cmds->is_err)
		*err = cmds->is_err;
	while (cmds && cmds->prev)
	{
		if (cmds->is_err)
			*err = cmds->is_err;
		cmds = cmds->prev;
	}
	return (cmds);
}

void		make_cmds_lst(t_ms *ms, t_parser *p)
{
	init_parser(p);
	while (ms->input[p->i])
	{
		if (p->slash_ig)
			p->i++;
		p->slash_ig = 0;
		if (ms->input[p->i] == '\\' && ++p->i)
			p->slash_ig = 1;
		if (ms->input[p->i] && !p->slash_ig)
		{
			if (ft_strchr("'\"", ms->input[p->i]))
				p->i += quote_handler(ms->input + p->i, 0);
			if (ft_strchr("|;><", ms->input[p->i]))
			{
				make_cmd(ms, p->j, &p->i, ms->input);
				p->j = p->i + 1 + skip_white_sp(ms->input + p->i + 1);
			}
			p->i++;
		}
	}
}

void		make_last_cmd(t_ms *ms, t_parser *p)
{
	if (!(ms->tab = parse_split(ms->input + p->j, ' ', ms)))
		errex(ms, SPLT_ERR);
	new_cmd(ms, S_COLON, ms->tab);
}

void		parse(t_ms *ms)
{
	t_parser p;

	ms->input = ft_strtrim(ms->input, " \t\n\v\f\r");
	parse_d(ms);
	make_cmds_lst(ms, &p);
	if (ms->input[p.j])
		make_last_cmd(ms, &p);
	ms->lst_end = ms->cmds;
	ms->head = get_head(ms->cmds, &ms->cmd_err);
	ms->cmds = ms->head;
}
