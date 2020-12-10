/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:33:16 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/08 20:55:09 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	char		*tmp;
	size_t		l;
	size_t		i;

	if (!s)
		return (NULL);
	substr = NULL;
	l = ft_strlen(s);
	if (start < l)
	{
		len = (len > (l - start)) ? (l - start) : len;
		if (!(substr = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		tmp = (char *)s + start;
		i = 0;
		while (i < len && tmp[i])
		{
			substr[i] = tmp[i];
			i++;
		}
		substr[i] = '\0';
		return (substr);
	}
	return (ft_strdup(""));
}
