/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:01:45 by obouykou          #+#    #+#             */
/*   Updated: 2020/11/04 10:03:43 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_arr(char **tab)
{
	int			i;
	int			chng;
	char		*tmp;

	chng = 1;
	while (chng)
	{
		chng = 0;
		i = 0;
		while (tab[i + 1])
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				chng = 1;
			}
			i++;
		}
	}
}
