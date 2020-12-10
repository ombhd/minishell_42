/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:28 by yslati            #+#    #+#             */
/*   Updated: 2020/12/10 13:36:04 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		sort_env(char **env)
{
	int		i;
	char	*pos;
	char	**arr;

	if (!(arr = dup_str_tab(env, '\0')))
		return ;
	ft_sort_arr(arr);
	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		if ((pos = ft_strchr(arr[i], '=')))
		{
			arr[i][(pos - arr[i])] = '\0';
			ft_putstr_fd(arr[i], 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pos + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd(arr[i], 1);
	}
	arr = free_str_table(arr);
}

int			valid_arg(char *arg)
{
	int		j;

	j = 0;
	if (!ft_isalpha(arg[0]))
		return (0);
	while (arg[++j] && arg[j] != '=')
		if (!ft_isalnum(arg[j]))
			return (0);
	return (1);
}

int			export_help(t_ms *ms, int i)
{
	int		len;

	len = 0;
	if ((len = check_exist(ms->env, ms->cmds->args[i])) != -1 ||
		(len = cmp_get_pos(ms->env, ms->cmds->args[i])) != -1)
	{
		free(ms->env[len]);
		free(ms->p_env[len]);
		ms->env[len] = ft_strdup(ms->cmds->args[i]);
		ms->p_env[len] = get_p_value(ms->cmds->args[i]);
	}
	else
	{
		ms->env = add_to_arr(ft_strdup(ms->cmds->args[i]), &ms->env, '\0');
		ms->p_env = add_to_arr(ft_strdup(ms->cmds->args[i]), &ms->p_env, 'p');
	}
	return (i);
}

int			ft_export(t_ms *ms)
{
	int		i;

	i = 0;
	if (!ms->cmds->args[1])
		sort_env(ms->env);
	else
		while (ms->cmds->args[++i])
		{
			if ((!ft_strcmp(ms->cmds->args[i], "_") ||
				!ft_strncmp(ms->cmds->args[i], "_=", 2)) && i++)
				continue ;
			if (!valid_arg(ms->cmds->args[i]) && cmd_error(ms, NOT_VALID_ERR,
			"export", ms->cmds->args[i]))
				continue;
			if (ft_strchr(ms->cmds->args[i], '='))
				i = export_help(ms, i);
			else if ((cmp_get_pos(ms->env, ms->cmds->args[i])) == -1)
			{
				ms->env = add_to_arr(ft_strdup(ms->cmds->args[i]),
									&ms->env, '\0');
				ms->p_env = add_to_arr(ft_strdup(ms->cmds->args[i]),
									&ms->p_env, '\0');
			}
		}
	return (0);
}
