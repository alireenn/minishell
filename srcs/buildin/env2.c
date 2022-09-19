/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:55:11 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/19 15:47:41 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

t_env	*copy_env(t_mini *mini, int *n)
{
	int		i;
	t_env	*it;
	t_env	*ret;
	t_env	*new;
	t_env	*tmp;

	it = mini->env;
	i = 1;
	tmp = malloc(sizeof(t_env));
	tmp->name_var = ft_strdup(it->name_var);
	tmp->arg_var = ft_strdup(it->arg_var);
	tmp->next = NULL;
	ret = tmp;
	it = it->next;
	while (it != NULL)
	{
		new = malloc(sizeof(t_env));
		new->name_var = ft_strdup(it->name_var);
		new->arg_var = ft_strdup(it->arg_var);
		new->next = NULL;
		tmp->next = new;
		tmp = new;
		it = it->next;
		i++;
	}
	(*n) = i;
	return (ret);
}

t_env	*ft_search_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(name) == ft_strlen(tmp->name_var)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

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
