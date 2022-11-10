/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:28:28 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/10 16:29:18 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe2(t_tree a, t_command **cmds, t_mini *mini, int fd[2])
{
	int		status[2];
	int		ret;
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		ret = execute(a->right, cmds, mini);
		close(fd[0]);
		exit(ret);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		waitpid(mini->pipe_pid1, &status[0], 0);
		waitpid(mini->pipe_pid1, &status[1], 0);
		dup2(mini->save_out, STDOUT_FILENO);
		dup2(mini->save_in, STDIN_FILENO);
		ret = (WEXITSTATUS(status[0]) && WEXITSTATUS(status[1]));
	}
	return (ret);
}

int	execute_pipe(t_tree a, t_command **cmds, t_mini *mini)
{
	int		fd[2];
	pid_t	pid1;
	int		ret;

	if (pipe(fd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		ret = execute(a->left, cmds, mini);
		close(fd[1]);
		exit(ret);
	}
	else
	{
		mini->pipe_pid1 = pid1;
		ret = execute_pipe2(a, cmds, mini, fd);
	}
	return (ret);
}
