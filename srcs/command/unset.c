/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouykou <obouykou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:04:34 by yslati            #+#    #+#             */
/*   Updated: 2020/12/05 20:36:36 by obouykou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			cmp_get_pos(char **env, char *var)
{
	int		i;
	char	*tmp;
	char	*pos;

	if ((pos = ft_strchr(var, '=')))
		tmp = ft_strldup(var, pos - var);
	else
		tmp = ft_strdup(var);
	i = -1;
	while (env[++i])
		if ((!ft_strcmp(env[i], tmp)))
		{
			tmp = ft_free(tmp);
			return (i);
		}
	return (get_env(env, tmp));
}

int			check_exist(char **env, char *arg)
{
	int		i;
	char	*wanted;
	char	*pos;

	if ((pos = ft_strchr(arg, '=')))
		wanted = ft_strldup(arg, pos - arg);
	else
		wanted = ft_strdup(arg);
	if (((i = get_env(env, wanted)) != -1))
		return (i);
	return (-1);
}

char		**rm_arr(char **env, int pos)
{
	char	**arr;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = -1;
	len = tb_len(env) - 1;
	if (!(arr = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (i < len)
		if (++j != pos)
			arr[i++] = ft_strdup(env[j]);
	arr[i] = NULL;
	free_str_table(env);
	return (arr);
}

int			ft_unset(t_ms *ms)
{
	int		i;
	int		len;

	len = 0;
	i = 1;
	while (ms->cmds->args[i])
	{
		if (ft_strchr(ms->cmds->args[i], '=') || !valid_arg(ms->cmds->args[i]))
		{
			cmd_error(ms, NOT_VALID_ERR, "unset", ms->cmds->args[i]);
			return (1);
		}
		else if ((len = cmp_get_pos(ms->env, ms->cmds->args[i])) != -1)
		{
			ms->env = rm_arr(ms->env, len);
			ms->p_env = rm_arr(ms->p_env, len);
		}
		i++;
	}
	return (0);
}
