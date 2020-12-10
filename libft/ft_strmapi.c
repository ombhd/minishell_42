/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 11:34:56 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/08 21:24:42 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	if (s && f)
	{
		if (!(i = ft_strlen(s)))
			return (ft_strdup(""));
		if (!(res = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		res[i] = '\0';
		!i ? i++ : i;
		while (--i)
			res[i] = (*f)(i, s[i]);
		res[i] = (*f)(i, s[i]);
		return (res);
	}
	return (NULL);
}
