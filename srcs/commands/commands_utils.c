/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 14:33:27 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/21 14:43:54 by anovelli         ###   ########.fr       */
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

void	make_cmd_helper(t_command *cmd, t_mini *mini)
{
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
}
