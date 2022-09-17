/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/15 18:46:38 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

t_command	**alloc_cmds(int cmd)
{
	t_command	**cmds;
	int			j;

	cmds = malloc (sizeof(t_command *) * cmd);
	j = 0;
	while (j < cmd)
	{
		cmds[j] = malloc(sizeof(t_command));
		j++;
	}
	return (cmds);
}

// void	expand(t_command *cmd, t_mini *mini)
// {
// 	int		i;
// 	int		len;
// 	char	*tmp;
// 	t_env	*var_env;

// 	i = 0;
// 	if (cmd->arg == NULL)
// 		return ;
// 	while (cmd->arg[i] != 0)
// 	{
// 		if (cmd->arg[i] == '$'
// 			&& cmd->arg[i + 1] != '\0' && cmd->arg[i + 1] != ' ')
// 		{
// 			len = 0;
// 			while (cmd->arg[i + 1 + len] != '\0'
// 				&& (cmd->arg[i + 1 + len] != ' '
// 					&& cmd->arg[i + 1 + len] != '$'))
// 				len++;
// 			if (len == 0 && cmd->arg[i + 1] == '$')
// 			{
// 				replace(&cmd->arg, i, i + 1, "pid");
// 				i++;
// 			}
// 			else if (len == 1 && cmd->arg[i + 1] == '?')
// 			{
// 				tmp = ft_itoa(mini->last);
// 				replace(&cmd->arg, i, i + len, tmp);
// 				free(tmp);
// 			}
// 			else
// 			{
// 				tmp = ft_strdup_from_to(cmd->arg, i + 1, i + len);
// 				var_env = ft_search_var(mini->env, tmp);
// 				if (var_env != NULL)
// 					replace(&cmd->arg, i, i + len, var_env->arg_var);
// 				else
// 					replace(&cmd->arg, i, i + len, NULL);
// 				free(tmp);
// 			}
// 		}
// 		i++;
// 	}
// }
