/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:01:21 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/07 13:18:21 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tmp0;
	char	*tmp1;

	tmp0 = (char *)src;
	tmp1 = (char *)dst;
	if (!tmp0 && !tmp1)
		return (NULL);
	if (tmp0 == tmp1)
		return (dst);
	if (tmp0 < tmp1)
	{
		tmp0 += len - 1;
		tmp1 += len - 1;
		while (len--)
			*tmp1-- = *tmp0--;
	}
	else
		while (len--)
			*tmp1++ = *tmp0++;
	return (dst);
}
