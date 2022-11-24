/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:19:42 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/24 18:17:49 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	int		x;

	tmp = malloc(sizeof(t_env));
	split_at(env[0], tmp, '=');
	mini->env = tmp;
	i = 1;
	while (env[i])
	{
		if (equal_strings(tmp->name_var, "SHLVL") == 0)
		{
			x = ft_atoi(tmp->arg_var);
			free(tmp->arg_var);
			tmp->arg_var = ft_itoa(x + 1);
		}
		new = malloc(sizeof(t_env));
		split_at(env[i], new, '=');
		tmp->next = new;
		tmp = new;
		i++;
	}
	tmp->next = NULL;
}

t_mini	*init_mini(char **envp)
{
	t_mini	*mini;

	mini = (t_mini *) malloc(sizeof(t_mini));
	if (mini == NULL)
		return (NULL);
	mini->exit = 0;
	init_env(mini, envp);
	mini->secret = NULL;
	init_secret_env(mini);
	mini->pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(mini->pwd, PATH_MAX);
	mini->save_out = dup(STDOUT_FILENO);
	mini->save_in = dup(STDIN_FILENO);
	mini->tree = NULL;
	mini->last = 0;
	mini->res = 1;
	mini->cmd = 0;
	return (mini);
}
