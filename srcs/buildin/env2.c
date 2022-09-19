/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:27:05 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/19 17:09:52 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

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