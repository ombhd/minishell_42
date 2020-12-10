/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:13:09 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/05 15:48:12 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!len || !*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 1;
		if (haystack[i] == needle[0])
		{
			while (needle[j] && (i + j) < len)
			{
				if (haystack[i + j] != needle[j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return ((char*)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
