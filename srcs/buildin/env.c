/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:24:11 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/19 15:47:33 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

void	split_at(char *input, t_env *env, char c)
{
	int		i;
	int		j;

	i = 0;
	while (input[i] != '\0' && input[i] != c)
		i++;
	j = 0;
	env->name_var = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		env->name_var[j] = input[j];
		j++;
	}
	env->name_var[j] = '\0';
	if (input[i] == '\0')
		env->arg_var = NULL;
	else
		env->arg_var = ft_strdup(&input[i + 1]);
	env->next = NULL;
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

void	ft_export(t_mini *mini, char *str, t_command *cmd)
{
	t_env	*tmp;

	if (str != NULL)
	{
		tmp = malloc (sizeof(t_env));
		split_at(str, tmp, '=');
		if (search(mini->env, tmp->name_var) == 0)
		{
			change_var(mini->env, tmp->name_var, tmp->arg_var);
			change_var(mini->secret, tmp->name_var, tmp->arg_var);
		}
		else if (search(mini->secret, tmp->name_var) == 0)
		{
			add_elem(&mini->env, tmp->name_var, tmp->arg_var);
			change_var(mini->secret, tmp->name_var, tmp->arg_var);
		}
		else
		{
			if (tmp->arg_var != NULL)
				add_elem(&mini->env, tmp->name_var, tmp->arg_var);
			add_elem_ord(&mini->secret, tmp->name_var, tmp->arg_var);
		}
		free(tmp->name_var);
		free(tmp->arg_var);
		free(tmp);
	}
	else
		ft_print_export(mini->secret, cmd);
	cmd->res = 1;
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
