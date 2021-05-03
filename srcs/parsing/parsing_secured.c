/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_secured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:49:58 by obouykou          #+#    #+#             */
/*   Updated: 2021/05/03 16:56:28 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**rm_empty_str(char **arr)
{
	int		i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[++i])
		if (!arr[i][0])
		{
			arr = rm_arr(arr, i);
			i--;
		}
	return (arr);
}

int is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' ||\
			c == '\f' || c == '\r');
}

int special_len(const char *str)
{
	int l;
	int i;

	l = ft_strlen(str) * 2;
	i = -1;
	while (str[++i])
	{
		if (is_space(str[i]))
			l--;
	}
	return (l);
}

char		*get_p_value(char *val)
{
	char	*p_var;
	char	*p_val;
	char	*pos;
	int		l;

	if (!(pos = ft_strchr(val, '=')))
		return (ft_strdup(val));
	l = pos - val + 1 + (2 * ft_strlen(pos + 1));
	p_var = (char *)malloc(sizeof(char) * (l + 1));
	p_val = (char *)malloc(sizeof(char) * (special_len(pos) - 1));
	ft_strlcpy(p_var, val, pos - val + 2);
	l = -1;
	while (*++pos)
	{
		if (!is_space(*pos))
			p_val[++l] = '\\';
		p_val[++l] = *pos;
	}
	p_val[++l] = '\0';
	ft_strcat(p_var, p_val);
	free(p_val);
	return (p_var);
}
