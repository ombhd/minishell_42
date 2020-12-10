/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 19:12:10 by obouykou          #+#    #+#             */
/*   Updated: 2019/10/30 16:30:29 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		l;

	l = 0;
	while (s[l])
		l++;
	if (s[l] == c)
		return ((char *)(s + l));
	while (--l >= 0)
		if (s[l] == c)
			return ((char *)(s + l));
	return (NULL);
}
