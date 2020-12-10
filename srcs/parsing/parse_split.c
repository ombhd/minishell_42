/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:58:28 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/07 14:07:17 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_words(char const *s, char c)
{
	int		len;
	int		i;
	char	slash_ig;

	if (!s)
		return (0);
	else if (!*s)
		return (-1);
	len = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		slash_ig = (i && s[i - 1] != '\\');
		if ((slash_ig || !i) && (s[i] == '\'' || s[i] == '"'))
			i += quote_handler(s + i, 0);
		slash_ig = (i && s[i - 1] != '\\');
		if (((slash_ig && (s[i] == c && s[i + 1] != c))) || s[i + 1] == '\0')
			len++;
		i++;
	}
	return (len);
}

int		ft_len_elem(char const *s, char c)
{
	int		i;
	int		size;
	int		ret;

	i = -1;
	size = 0;
	while (s[++i] && (s[i] != c || (i && s[i - 1] == '\\')))
	{
		if (((i && s[i - 1] != '\\') || !i) && (s[i] == '\'' || s[i] == '"'))
		{
			ret = quote_handler(s + i, 0);
			size += ret;
			i += ret;
		}
		if (s[i] != c || (i && s[i - 1] == '\\'))
			size++;
	}
	return (size);
}

char	*fill_elem(char **elem, char *s, char c, t_ms *ms)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (s[j] && (s[j] != c || (j && s[j - 1] == '\\')))
	{
		quote = 0;
		if (((j && s[j - 1] != '\\') || !j) && (s[j] == '\'' || s[j] == '"'))
		{
			quote = s[j];
			(*elem)[i++] = s[j++];
			while (s[j] && (s[j] != quote || ((j && s[j - 1] == '\\') || !j)))
				(*elem)[i++] = s[j++];
			if (s[j])
				(*elem)[i++] = s[j++];
		}
		if (s[j] && !quote)
			(*elem)[i++] = s[j++];
	}
	(*elem)[i] = '\0';
	*elem = parse_quote_bslash(*elem, ms);
	return (s + j);
}

char	**for_empty_str(void)
{
	char **tab;

	if (!(tab = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	tab[1] = NULL;
	tab[0] = ft_strdup("");
	return (tab);
}

char	**parse_split(char const *s, char c, t_ms *ms)
{
	char	**tab;
	int		j;
	int		l;

	if ((l = ft_words(s, c)) == -1)
		return (for_empty_str());
	j = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (l + 1))))
		return (NULL);
	tab[l] = NULL;
	while (j < l)
	{
		while (*s && *s == c)
			s++;
		if (!(tab[j] = (char *)malloc((ft_len_elem(s, c) + 1) * sizeof(char))))
			return (free_str_table(tab));
		s = fill_elem(&tab[j++], (char *)s, c, ms);
	}
	return (tab);
}
