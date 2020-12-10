/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:22:05 by obouykou          #+#    #+#             */
/*   Updated: 2019/10/30 12:08:35 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content)
{
	t_list	*l;

	if (!(l = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	l->content = content;
	l->next = NULL;
	return (l);
}
