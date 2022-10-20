/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:00:20 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/22 19:00:50 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
		free(argv);
	}
	if (envp != NULL)
	{
		i = 0;
		while (envp[i] != NULL)
		{
			free(envp[i]);
			i++;
		}
		free(envp);
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

void	free_matrix(char **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_matrix_no_rows(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	if (matrix != NULL)
		free(matrix);
}
