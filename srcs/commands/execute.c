/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:21:27 by gcucino           #+#    #+#             */
/*   Updated: 2022/10/26 15:31:42 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../incl/minishell.h"

char	*get_filename(t_mini *mini, char *filename)
{
	char	*ret;
	char	**path;
	int		i;

	ret = NULL;
	if (is_valid_path(filename) == 1)
		return (ft_strdup(filename));
	if (ft_strchr(filename, '/') != NULL)
	{
		printf_fd(2, "minishell: %s: No such file or directory\n", filename);
		exit(127);
	}
	path = get_path(mini);
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		ret = check_path(filename, path, i);
		if (ret != NULL)
			return (ret);
		i++;
	}
	free(path);
	return (NULL);
}

char	**get_argv(char *com, char *arg)
{
	char	*tmp;
	char	**argv;

	if (arg == NULL)
	{
		argv = malloc(sizeof(char *) * 2);
		argv[0] = ft_strdup(com);
		argv[1] = NULL;
	}
	else
	{
		tmp = ft_join_char(com, arg, ' ');
		argv = mod_split(tmp, " ", "\'\"");
		free(tmp);
	}
	return (argv);
}

void	other_command(t_command *cmd, t_mini *mini)
{
	pid_t	pid;
	int		ret;
	int		status;

	pid = fork();
	if (pid == 0)
		other_command_helper(mini, cmd);
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
	t_mini	*mini2;
	char	**envp2;
	char	*new_cmd;

	if (cmd->red[0] != 0 || cmd->red[1] != 0)
	{
		if (cmd->fd_red[0] < 0)
			return ;
		change_fd(cmd);
	}
	if (cmd->com == NULL)
		cmd->res = 1;
	else if (cmd->com[0] == '(')
	{
		new_cmd = ft_strdup_from_to(cmd->com, 1, ft_strlen(cmd->com) - 2);
		envp2 = trasformation(mini->env);
		mini2 = init_mini(envp2);
		process_input(mini2, new_cmd);
		cmd->res = mini2->res;
	}
	else
		make_cmd_helper(cmd, mini);
	if (cmd->red[0] != 0 || cmd->red[1] != 0)
		back_to_standard(cmd, mini);
}

int	execute_pipe(t_tree a, t_command **cmds, t_mini *mini)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		ret;
	int		status1;
	int		status2;

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
			waitpid(pid1, &status1, 0);
			waitpid(pid1, &status2, 0);
			dup2(mini->save_out, STDOUT_FILENO);
			dup2(mini->save_in, STDIN_FILENO);
			ret = WEXITSTATUS(status1) && WEXITSTATUS(status2);
		}
	}
	// dup2(fd[1], STDOUT_FILENO);
	// ret = execute(a->left, cmds, mini);
	// close(fd[1]);
	// dup2(mini->save_out, STDOUT_FILENO);
	// dup2(fd[0], STDIN_FILENO);
	// ret = execute(a->right, cmds, mini);
	// close(fd[0]);
	// dup2(mini->save_in, STDIN_FILENO);
	return (ret);
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
		return (execute_pipe(a, cmds, mini));
	else
	{
		make_cmd(cmds[a->info], mini);
		return (cmds[a->info]->res);
	}
}
