/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:11:07 by obouykou          #+#    #+#             */
/*   Updated: 2019/10/24 14:01:36 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return ((char *)s + i);
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}
