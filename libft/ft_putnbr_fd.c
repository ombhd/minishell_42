/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:18:49 by obouykou          #+#    #+#             */
/*   Updated: 2019/10/24 14:01:31 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = -i;
	}
	if (i > 9)
	{
		ft_putnbr_fd((i / 10), fd);
		ft_putnbr_fd((i % 10), fd);
	}
	else
		ft_putchar_fd('0' + i, fd);
}
