/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:51:26 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/07 11:18:23 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		len;

	if (!size)
		return (ft_strlen(src));
	len = ft_strlen(dst) + ft_strlen(src);
	i = ft_strlen(dst);
	j = 0;
	if (size <= i)
		return (ft_strlen(src) + size);
	while (src[j] && i < size - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len);
}
