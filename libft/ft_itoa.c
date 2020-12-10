/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:21:33 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/08 21:41:34 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	static	*ft_fill(char *res, long n, int i, int b)
{
	if (!n)
	{
		res[0] = '0';
		return (res);
	}
	if (!b)
	{
		n = -n;
		res[0] = '-';
	}
	while (n)
	{
		res[--i] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}

char			*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		l;
	int		b;

	l = 1;
	(!n) ? l++ : l;
	b = 0;
	(n < 0) ? l++ : b++;
	i = -n;
	while (i)
	{
		l++;
		i /= 10;
	}
	res = (char *)malloc(l * sizeof(char));
	if (!res)
		return (NULL);
	i = l - 1;
	res[i] = '\0';
	res = ft_fill(res, n, i, b);
	return (res);
}
