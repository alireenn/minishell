/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:27:05 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/18 14:56:27 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_unset(t_mini *mini, char *name, t_command *cmd)
{
	t_env	*tmp;
	t_env	*tmp2;

	if (ft_strchr(name, '=') != NULL)
	{
		printf("minishell: unset: '%s': not a valid identifier\n", name);
		cmd->res = 0;
		return ;
	}
	tmp = ft_search_var(mini->env, name);
	tmp2 = ft_search_var(mini->secret, name);
	if (tmp != NULL)
		delete_elem(&mini->env, tmp);
	if (tmp2 != NULL)
		delete_elem(&mini->secret, tmp2);
	cmd->res = 1;
}

int	search(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->name_var) == ft_strlen(name)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(tmp->name_var)) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_export_supp(t_mini *mini, t_env *tmp)
{
	if (search(mini->secret, tmp->name_var) == 0)
	{
		if (tmp->arg_var != NULL)
		{
			tmp->arg_var = remove_quotes_str(tmp->arg_var);
			add_elem(&mini->env, tmp->name_var, tmp->arg_var);
		}
		change_var(mini->secret, tmp->name_var, tmp->arg_var);
	}
	else
	{
		if (tmp->arg_var != NULL)
		{
			tmp->arg_var = remove_quotes_str(tmp->arg_var);
			add_elem(&mini->env, tmp->name_var, tmp->arg_var);
		}
		add_elem_ord(&mini->secret, tmp->name_var, tmp->arg_var);
	}
	return ;
}
