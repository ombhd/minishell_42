/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:29:43 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/03 10:22:15 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *src, int l)
{
	int		i;
	char	*dup;

	dup = (char*)malloc(sizeof(char) * (l + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < l)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
