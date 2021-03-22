/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_chars_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:52:38 by obouykou          #+#    #+#             */
/*   Updated: 2021/03/22 19:06:49 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		quote_handler(char const *s, int neg)
{
	char	quote;
	char	slash_ig;
	int		i;

	i = 1;
	quote = s[0];
	slash_ig = 0;
	if (quote == '\'')
		while (s[i] && s[i] != quote)
			i++;
	else
		while (s[i])
		{
			if (slash_ig == 1)
				i++;
			slash_ig = 0;
			if (s[i] == '\\' && (++i) && (slash_ig = 1))
				continue ;
			if (s[i] == quote)
				break ;
			i++;
		}
	if (!s[i])
		return (!neg ? (i - 1) : (-1));
	return (i);
}

char	*remove_bslash(char *elem, int i, char *err)
{
	char *tmp;

	if (!elem[i + 1])
	{
		*err = STX_ERR;
		return (elem);
	}
	tmp = ft_strdup(elem);
	tmp[i++] = '\0';
	ft_strcat(tmp, elem + i);
	free(elem);
	return (tmp);
}

char	*catch_bslash(char *elem, t_ms *ms, int j, int *e)
{
	while (elem[++j] && j < *e)
		if (elem[j] == '\\' && elem[j + 1] && ft_strchr("$\"\\", elem[j + 1]))
		{
			elem = remove_bslash(elem, j, &ms->cmd_err);
			--*e;
			if (elem[j] == '$')
				continue;
		}
	return (elem);
}

char	*remove_quotes(char *elem, int *i, int e, t_ms *ms)
{
	char	*tmp;

	if (elem[*i] == '"')
		elem = catch_bslash(elem, ms, *i, &e);
	tmp = ft_strdup(elem);
	tmp[(*i)++] = '\0';
	ft_strcat(tmp, elem + *i);
	tmp[e - 1] = '\0';
	ft_strcat(tmp, elem + ++e);
	free(elem);
	*i = e - 3;
	return (tmp);
}

char	*parse_quote_bslash(char *elem, t_ms *ms)
{
	int		i;
	int		l;

	elem = ft_strtrim(elem, "\v\t\n\f\r");
	i = -1;
	while (elem[++i])
	{
		if (ft_strchr("\"'", elem[i]) && ((i && elem[i - 1] != '\\') || !i))
		{
			if ((l = quote_handler(elem + i, 1)) < 0)
			{
				ms->cmd_err = 1;
				break ;
			}
			elem = remove_quotes(elem, &i, i + l, ms);
			continue ;
		}
		if (elem[i] == '\\')
			elem = remove_bslash(elem, i, &ms->cmd_err);
	}
	return (elem);
}
