/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:00:20 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 18:10:22 by gcucino          ###   ########.fr       */
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
