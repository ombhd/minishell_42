/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:30:57 by obouykou          #+#    #+#             */
/*   Updated: 2019/10/26 12:13:04 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char		*res;
	size_t		i;

	res = (char *)malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < (count * size))
		res[i++] = 0;
	return ((void*)res);
}
