/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:58:32 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/03 15:01:44 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp0;
	unsigned char	*tmp1;

	tmp0 = (unsigned char *)src;
	tmp1 = (unsigned char *)dst;
	if (!tmp0 && !tmp1)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*tmp1 = *tmp0;
		tmp1++;
		i++;
		if (*tmp0++ == (unsigned char)c)
		{
			return (tmp1);
		}
	}
	return (NULL);
}
