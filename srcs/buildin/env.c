/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:24:11 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/11 17:38:53 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_tmp(t_env *tmp)
{
	free(tmp->name_var);
	free(tmp->arg_var);
	free(tmp);
}

char	**trasformation(t_env *env)
{
	int		i;
	char	**m;
	int		size;
	t_env	*tmp;

	tmp = env;
	i = 0;
	size = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	m = (char **)malloc (sizeof(char *) * (size + 1));
	tmp = env;
	while (tmp != NULL)
	{
		m[i] = ft_join_char(tmp->name_var, tmp->arg_var, '=');
		i++;
		tmp = tmp->next;
	}
	m[i] = NULL;
	return (m);
}

void	ft_env(t_env *env, t_command *cmd)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->arg_var != NULL)
			printf("%s=%s\n", tmp->name_var, tmp->arg_var);
		else
			printf("%s\n", tmp->name_var);
		tmp = tmp->next;
	}
	cmd->res = 1;
}
