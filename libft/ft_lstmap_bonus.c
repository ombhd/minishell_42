/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:38:59 by obouykou          #+#    #+#             */
/*   Updated: 2019/11/03 18:26:15 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lr;
	t_list	*lt;

	lr = NULL;
	while (lst)
	{
		if (!(lt = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&lr, del);
			return (NULL);
		}
		ft_lstadd_back(&lr, lt);
		lst = lst->next;
	}
	return (lr);
}
