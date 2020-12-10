/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_secured.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:49:58 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/10 11:51:08 by obouykou         ###   ########.fr       */
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
	p_val = (char *)malloc(sizeof(char) * ((ft_strlen(pos) * 2) - 1));
	ft_strlcpy(p_var, val, pos - val + 2);
	l = -1;
	while (*++pos)
	{
		p_val[++l] = '\\';
		p_val[++l] = *pos;
	}
	p_val[++l] = '\0';
	ft_strcat(p_var, p_val);
	free(p_val);
	return (p_var);
}
