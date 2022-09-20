/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:00:20 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/20 17:21:42 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../incl/new_parser.h"

void	free_execve(char *filename, char **argv, char **envp)
{
	int	i;

	if (filename != NULL)
		free(filename);
	if (argv != NULL)
	{
		i = 0;
		while (argv[i] != NULL)
		{
			free(argv[i]);
			i++;
		}
	}
	if (envp != NULL)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			free(envp[i]);
			i++;
		}
	}
}

void	free_cmds(t_command	**cmds, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		if (cmds[i]->com != NULL)
			free(cmds[i]->com);
		if (cmds[i]->arg != NULL)
			free(cmds[i]->arg);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_env(t_env *env)
{
	if (env->next == NULL)
	{
		free(env->name_var);
		free(env->arg_var);
		free(env);
		return ;
	}
	else
	{
		free_env(env->next);
		free(env->name_var);
		free(env->arg_var);
		free(env);
	}
}

void	free_mini(t_mini *mini)
{
	if (mini->env != NULL)
		free_env(mini->env);
	if (mini->secret != NULL)
		free_env(mini->secret);
	if (mini->pwd != NULL)
		free(mini->pwd);
	free(mini);
}
