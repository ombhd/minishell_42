/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:53:34 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/05 15:14:30 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *t;

	if (!new)
		return ;
	t = *alst;
	new->next = NULL;
	if (!t)
	{
		*alst = new;
		return ;
	}
	while (t->next)
		t = t->next;
	t->next = new;
}
