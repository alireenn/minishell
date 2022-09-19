/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:21:27 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 16:30:18 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

void	other_command(t_command *cmd, t_mini *mini)
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**envp;
	char	**argv;
	char	*filename;

	pid = fork();
	if (pid == 0)
	{
		envp = trasformation(mini->env);
		argv = get_argv(cmd->com, cmd->arg);
		filename = get_filename(mini, cmd->com);
		if (execve(filename, argv, envp) == -1)
		{
			free_execve(filename, argv, envp);
			printf_fd(2, "minishell: %s: command not found\n", cmd->com);
			exit(127);
		}
		free_execve(filename, argv, envp);
		exit(0);
	}
	ret = wait(&status);
	if (ret == -1)
		exit(-1);
	if (WEXITSTATUS(status) == 0)
		cmd->res = 1;
	else
	{
		mini->last = WEXITSTATUS(status);
		cmd->res = 0;
	}
}

void	make_cmd(t_command *cmd, t_mini *mini)
{
	expand(cmd, mini);
	if (cmd->red[0] != 0 || cmd->red[1] != 0)
	{
		if (cmd->fd_red[0] < 0)
			return ;
		change_fd(cmd);
	}
	if (equal_strings(cmd->com, "echo") == 0)
		ft_echo(cmd->arg, cmd);
	else if (equal_strings(cmd->com, "pwd") == 0)
		ft_pwd(cmd);
	else if (equal_strings(cmd->com, "env") == 0)
		ft_env(mini->env, cmd);
	else if (equal_strings(cmd->com, "export") == 0)
		ft_export(mini, cmd->arg, cmd);
	else if (equal_strings(cmd->com, "unset") == 0)
		ft_unset(mini, cmd->arg, cmd);
	else if (equal_strings(cmd->com, "exit") == 0)
		ft_exit(mini, cmd);
	else if (equal_strings(cmd->com, "cd") == 0)
		ft_cd(mini, cmd->arg, cmd);
	else
		other_command(cmd, mini);
	if (cmd->red[0] != 0 || cmd->red[1] != 0)
		back_to_standard(cmd, mini);
}

int	execute(t_tree a, t_command **cmds, t_mini *mini)
{
	if (mini->exit == 1)
		return (1);
	if (a->info == -1)
		return (execute(a->left, cmds, mini) && execute(a->right, cmds, mini));
	if (a->info == -2)
		return (execute(a->left, cmds, mini) || execute(a->right, cmds, mini));
	if (a->info == -3)
	{
		printf("pipe non ancora implementate\n");
		exit(1);
	}
	else
	{
		make_cmd(cmds[a->info], mini);
		return (cmds[a->info]->res);
	}
}
