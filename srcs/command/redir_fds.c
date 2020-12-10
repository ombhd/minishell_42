/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:55:45 by yslati            #+#    #+#             */
/*   Updated: 2020/12/10 13:37:15 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				open_file(t_cmd *tmp)
{
	int			fd;

	fd = 1;
	if (tmp->redir == TRUNC)
		fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (tmp->redir == APPEND)
		fd = open(tmp->next->cmd, O_WRONLY | O_CREAT | O_APPEND, 0666);
	return (fd);
}

void			read_file(t_ms *ms, t_cmd *tmp)
{
	int		fd;

	fd = 0;
	if ((fd = open(tmp->next->cmd, O_RDONLY)) < 0)
	{
		cmd_error(ms, F_NOT_FOUND_ERR, NULL, tmp->next->cmd);
		exit(1);
	}
	else
		dup2(fd, 0);
	close(fd);
}

void			save_fds(int *fds)
{
	fds[0] = dup(0);
	fds[1] = dup(1);
	fds[2] = dup(2);
}

void			restore_fds(int *fds)
{
	dup2(fds[0], 0);
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	dup2(fds[2], 2);
	close(fds[2]);
}

void			ft_redir(t_ms *ms, t_cmd *tmp, t_cmd *cmd)
{
	int			i;
	int			fd_in;

	if (ms->cmds->next->cmd[0] == '\0' &&
		cmd_error(ms, F_NOT_FOUND_ERR, NULL, ""))
		exit(1);
	while (tmp && tmp->redir)
	{
		i = 1;
		if (tb_len(tmp->next->args) > 1 && !tmp->next->start)
			while (tmp->next->args[i])
				cmd->args = get_arr(ft_strdup(tmp->next->args[i++]),
									&cmd->args, '\0');
		if (tmp->redir == TRUNC || tmp->redir == APPEND)
			fd_in = open_file(tmp);
		else if (tmp->redir == READ)
			read_file(ms, tmp);
		tmp = tmp->next;
	}
	if (cmd->redir == TRUNC || cmd->redir == APPEND)
	{
		dup2(fd_in, 1);
		close(fd_in);
	}
}
