/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:37:11 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/24 10:53:22 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_print_export(t_env *env, t_command *cmd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->arg_var != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->name_var, tmp->arg_var);
		else
			printf("declare -x %s\n", tmp->name_var);
		tmp = tmp->next;
	}
	cmd->res = 1;
}

void	ft_export_replace(t_mini *mini, t_env *tmp, t_command *cmd)
{
	if (search(mini->env, tmp->name_var) == 0)
		export_error(tmp, mini, cmd, 1);
	else
		ft_export_supp(mini, tmp);
	free_tmp(tmp);
}

void	ft_export(t_mini *mini, char *str, t_command *cmd)
{
	t_env	*tmp;

	if (str != NULL)
	{
		tmp = malloc (sizeof(t_env));
		split_at(str, tmp, '=');
		if (check_env_var(tmp->name_var) == 0)
		{
			export_error(tmp, mini, cmd, 0);
			return ;
		}
		ft_export_replace(mini, tmp, cmd);
	}
	else
		ft_print_export(mini->secret, cmd);
	cmd->res = 1;
}

void	export_error(t_env *tmp, t_mini *mini, t_command *cmd, int flag)
{
	if (flag == 0)
	{
		printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
			tmp->name_var);
		mini->last = 1;
		cmd->res = 0;
	}
	if (flag == 1 && tmp->arg_var != NULL)
	{
		change_var(mini->env, tmp->name_var, tmp->arg_var);
		change_var(mini->secret, tmp->name_var, tmp->arg_var);
	}
}

void	export_unset(t_mini *mini, t_command *cmd)
{
	char	**split;
	int		i;

	i = 0;
	if (equal_strings(cmd->com, "export") == 0)
	{
		if (cmd->arg != NULL)
		{
			split = mod_split(cmd->arg, " ", "\'\"");
			i = 0;
			while (split[i])
			{
				ft_export(mini, split[i], cmd);
				free(split[i]);
				i++;
			}
			free(split);
		}
		else
			ft_export(mini, cmd->arg, cmd);
	}
	else if (equal_strings(cmd->com, "unset") == 0)
		unset_help(cmd, mini);
}
