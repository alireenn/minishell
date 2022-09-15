/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/15 17:29:04 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	init_secret_env(t_mini *mini)
{
	t_env	*it;
	t_env	*min;
	t_env	*tmp;
	int		i;
	int		cmp;

	tmp = copy_env(mini, &i);
	while (i--)
	{
		it = tmp;
		min = tmp;
		while (it != NULL)
		{
			cmp = ft_strncmp(it->name_var, min->name_var,
					ft_strlen(min->name_var));
			if (cmp < 0 || (cmp == 0 && ft_strlen(it->name_var)
					< ft_strlen(min->name_var)))
				min = it;
			it = it->next;
		}
		add_elem(&mini->secret, min->name_var, min->arg_var);
		delete_elem(&tmp, min);
	}
	free(tmp);
}

void	init_env(t_mini *mini, char **env)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	split_at(env[0], tmp, '=');
	mini->env = tmp;
	i = 1;
	while (env[i])
	{
		new = malloc(sizeof(t_env));
		split_at(env[i], new, '=');
		tmp->next = new;
		tmp = new;
		i++;
	}
}

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
