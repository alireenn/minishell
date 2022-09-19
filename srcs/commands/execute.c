/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:21:27 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 18:29:47 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

char	**get_path(t_mini *mini)
{
	t_env	*path;
	int		i;

	i = 0;
	path = mini->env;
	while (path != NULL)
	{
		if (ft_strlen(path->name_var) == 4
			&& ft_strncmp(path->name_var, "PATH",
				ft_strlen(path->name_var)) == 0)
			break ;
		path = path->next;
	}
	if (path != NULL)
		return (ft_split(path->arg_var, ":", &i));
	return (NULL);
}

int	is_valid_path(char *filename)
{
	DIR	*dir;

	if (access(filename, F_OK) == 0)
	{
		if (access(filename, X_OK) != 0)
		{
			printf_fd(2, "minishell: %s: Permission denied\n", filename);
			exit(126);
		}
		else
		{
			dir = opendir(filename);
			if (dir != NULL)
			{
				printf_fd(2, "minishell: %s: is a directory\n", filename);
				closedir(dir);
				exit(126);
			}
		}
		return (1);
	}
	return (0);
}

char	*get_filename(t_mini *mini, char *filename)
{
	char	*ret;
	char	**path;
	int		i;

	ret = NULL;
	if (is_valid_path(filename) == 1)
		return (ft_strdup(filename));
	if (strchr(filename, '/') != NULL)
	{
		printf_fd(2, "minishell: %s: No such file or directory\n", filename);
		exit(1);
	}
	path = get_path(mini);
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		ret = ft_join_char(path[i], filename, '/');
		if (access(ret, F_OK) == 0)
		{
			if (access(ret, X_OK) != 0)
			{
				printf_fd(2, "minishell: %s: Permission denied\n", filename);
				exit(126);
			}
			return (ret);
		}
		free(ret);
		i++;
	}
	return (NULL);
}

char	**get_argv(char *com, char *arg)
{
	char	*tmp;
	char	**argv;
	int		i;

	i = 0;
	tmp = ft_join_char(com, arg, ' ');
	argv = ft_split(tmp, " ", &i);
	free(tmp);
	return (argv);
}

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
