/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_total_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:21:10 by obouykou          #+#    #+#             */
/*   Updated: 2021/02/23 13:02:24 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		sm_finder(char *input, t_parser *p)
{
	int		r;

	if (input[p->i] && ft_strchr("'\"", input[p->i]))
	{
		if ((r = quote_handler(input + p->i, 1)) < 0)
			return (STX_ERR);
		p->i += r;
	}
	if (input[p->i] == ';')
	{
		p->j = p->i + 1;
		p->m = p->j + skip_white_sp(input + p->j);
		if (input[p->m] == ';')
			return (STX_ERR);
		p->l++;
	}
	return (SUCCESS);
}

int		get_hm_cmds(char *input, t_parser *p)
{
	init_parser(p);
	while (input[p->i])
	{
		if (p->slash_ig)
			p->i++;
		p->slash_ig = 0;
		if (input[p->i] == '\\' && ++p->i)
			p->slash_ig = 1;
		if (!p->slash_ig)
			if (sm_finder(input, p) == STX_ERR)
				return (-1);
		if (!p->slash_ig)
			p->i++;
	}
	if (input[p->m])
		p->l++;
	return (p->l);
}

int		stx_handler(char **input, t_parser *p)
{
	// int i;
	// char *tmp;

	// i = 0;
	// while (input[0][i] == ' ' || input[0][i] == '\t')
	// 	i++;
	// if (i && (tmp = *input))
	// {
	// 	*input = ft_strdup(*input + i);
	// 	free(tmp);
	// }
	p->m = input[0][skip_white_sp(*input)];
	if (!p->m || p->m == ';')
	{
		free(*input);
		*input = NULL;
		return (!p->m ? 0 : STX_ERR);
	}
	if (get_hm_cmds(*input, p) < 0)
	{
		free(*input);
		*input = NULL;
		return (STX_ERR);
	}
	return (VALID_STX);
}

void	get_cmds_tab(char *input, char **cmd_tab, t_parser *p)
{
	init_parser(p);
	p->i = -1;
	while (input[++p->i])
	{
		p->slash_ig = ((p->i && input[p->i - 1] != '\\') || !p->i);
		if (ft_strchr("'\"", input[p->i]) && p->slash_ig)
			p->i += quote_handler(input + p->i, 1);
		p->slash_ig = ((p->i && input[p->i - 1] != '\\') || !p->i);
		if (input[p->i] == ';' && p->slash_ig)
		{
			cmd_tab[p->m++] = ft_substr(input, p->j, p->i - p->j);
			p->j = p->i + 1 + skip_white_sp(input + p->i + 1);
		}
	}
	if (input[p->j])
		cmd_tab[p->m] = ft_substr(input, p->j, p->i - p->j);
}

int		parse_total_cmds(t_ms *ms)
{
	t_parser p;

	get_input(ms);
	if ((p.m = stx_handler(&ms->input, &p)) != VALID_STX)
		return (p.m);
	ms->cmd_tab = (char **)malloc(sizeof(char *) * (p.l + 1));
	ms->cmd_tab[p.l] = NULL;
	get_cmds_tab(ms->input, ms->cmd_tab, &p);
	ms->input = ft_free(ms->input);

	return (0);
}
