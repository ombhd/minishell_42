/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:48:16 by obouykou          #+#    #+#             */
/*   Updated: 2020/12/06 20:45:56 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_next_line(int fd, char **line)
{
	static	char	*buff_s;
	char			*buff;
	int				b;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 ||
		!line || !(*line = (char *)malloc(1 * sizeof(char))))
		return (-1);
	**line = '\0';
	b = 1;
	if (!(buff = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (b)
	{
		if (!buff_s && (b = read(fd, buff, BUFFER_SIZE)) == -1)
			return (-1);
		buff[b] = '\0';
		if (!buff_s && build_line(line, &buff, &(buff_s), 1))
			return (1);
		else if (buff_s && build_line(line, &buff, &(buff_s), 0))
			return (1);
	}
	free(buff_s);
	free(buff);
	return (0);
}
