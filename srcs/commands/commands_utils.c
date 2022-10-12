/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:33:27 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/12 15:49:40 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

char	*check_path(char *filename, char **path, int i)
{
	char	*ret;

	ret = ft_join_char(path[i], filename, '/');
	if (access(ret, F_OK) == 0)
	{
		if (access(ret, X_OK) != 0)
		{
			printf_fd(2, "minishell: %s: Permission denied\n", filename);
			exit(126);
		}
		free(path);
		return (ret);
	}
	free(ret);
	return (NULL);
}

void	other_command_helper(t_mini *mini, t_command *cmd)
{
	char	**envp;
	char	**argv;
	char	*filename;

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
	exit (0);
}

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

void	make_cmd_helper(t_command *cmd, t_mini *mini)
{
	if (equal_strings(cmd->com, "echo") == 0)
		ft_echo(cmd->arg, cmd);
	else if (equal_strings(cmd->com, "pwd") == 0)
		ft_pwd(cmd);
	else if (equal_strings(cmd->com, "env") == 0)
	{
		if (cmd->arg == NULL)
			ft_env(mini->env, cmd);
		else
		{
			printf("env: %s: No such file or directory\n", cmd->arg);
			mini->last = 127;
		}
	}
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
}
