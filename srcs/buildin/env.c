/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:24:11 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/11 15:42:04 by anovelli         ###   ########.fr       */
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

void	ft_export(t_mini *mini, char *str, t_command *cmd)
{
	t_env	*tmp;
	int		i;
	int flag;

	flag = 0;
	i = 0;
	if (str != NULL)
	{
		if (ft_strchr(str, ' ') != 0)
			flag = 1;
		tmp = malloc (sizeof(t_env));
		split_at(str, tmp, '=');
		if (check_env_var(tmp->name_var) == 0)
		{
			export_error(tmp, mini, cmd, 0);
			return ;
		}
		else if (search(mini->env, tmp->name_var) == 0)
			export_error(tmp, mini, cmd, 1);
		else
			ft_export_supp(mini, tmp);
		free_tmp(tmp);
	}
	else
		ft_print_export(mini->secret, cmd);
	cmd->res = 1;
}
