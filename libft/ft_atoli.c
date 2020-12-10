/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoli.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:00:02 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/05 20:49:50 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long		get_ret(long a, int sign)
{
	if (a < 0 && sign > 0)
		return (-1);
	if (a > 0 && sign < 0)
		return (0);
	return (a);
}

long		ft_atoli(const char *str)
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
	return (get_ret(a, sign));
}
