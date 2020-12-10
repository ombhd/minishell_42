/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:00:02 by obouykou          #+#    #+#             */
/*   Updated: 2020/10/26 11:51:49 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_help(long a, int sign)
{
	if (a < 0 && sign > 0)
		return (-1);
	if (a > 0 && sign < 0)
		return (0);
	return (a);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	a;

	a = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] > '9' || str[i] < 48)
			break ;
		a = (a * 10) + str[i] - 48;
		i++;
	}
	a = a * sign;
	return (ft_help(a, sign));
}
