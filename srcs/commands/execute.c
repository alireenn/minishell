/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:21:27 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/05 17:21:12 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

	/*else if (ft_strchr(arg, '*') != 0)
	{
		argv = what_team(ft_pwd_ft(), arg, com);
		if (argv[1] == NULL)
		{
			argv[1] = ft_strdup(arg);
			argv[2] = NULL;
		}
	}*/
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
		free_subshell(mini2, envp2, new_cmd);
	}
	else
		make_cmd_helper(cmd, mini);
	if (cmd->red[0] != 0 || cmd->red[1] != 0)
		back_to_standard(cmd, mini);
}

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

/*
	dup2(fd[1], STDOUT_FILENO);
	ret = execute(a->left, cmds, mini);
	close(fd[1]);
	dup2(mini->save_out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	ret = execute(a->right, cmds, mini);
	close(fd[0]);
	dup2(mini->save_in, STDIN_FILENO);
*/

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

int	here_doc(char *end)
{
	pid_t	reader;
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		return (-1);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		rl_already_prompted = 0;
		tmp = readline("> ");
		rl_already_prompted = 1;
		while (ft_strlen(tmp) != ft_strlen(end)
			|| ft_strncmp(tmp, end, ft_strlen(end)) != 0)
			tmp = here_doc_helper(fd, tmp);
		free(tmp);
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		return (fd[0]);
	}
}
