/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/02 22:15:35 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_command	**alloc_cmds(int cmd)
{
	t_command	**cmds;
	int			j;

	cmds = malloc (sizeof(t_command *) * cmd);
	j = 0;
	while (j < cmd)
	{
		cmds[j] = malloc(sizeof(t_command));
		j++;
	}
	return (cmds);
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
	if (WEXITSTATUS(status) == 0 && WIFSIGNALED(status) == 0)
		cmd->res = 1;
	else if (WIFSIGNALED(status))
	{
		mini->last = WTERMSIG(status) + 128;
		cmd->res = 0;
	}
	else
	{
		mini->last = WEXITSTATUS(status);
		cmd->res = 0;
	}
}

void	get_cmd_simple(t_command **cmds, char **input, int i, int j)
{
	char	*tmp;

	if (input[i][j] == '\"' || input[i][j] == '\'')
		j = search_closing(input[i], j, input[i][j], input[i][j]);
	while ((input[i][j] != ' ' && input[i][j] != '\t')
			&& j < (int)ft_strlen(input[i]))
		j++;
	if (j == 0)
		cmds[i]->com = NULL;
	else
	{
		tmp = get_strip_str(input[i], 0, j, 0);
		cmds[i]->com = remove_quotes_str(tmp);
		free(tmp);
	}
	while (input[i][j] != ' ' && input[i][j] != '\t'
			&& j < (int)ft_strlen(input[i]))
		j++;
	if (j == (int)ft_strlen(input[i]))
		cmds[i]->arg = NULL;
	else
	{
		cmds[i]->arg = get_strip_str(input[i], j, (int)ft_strlen(input[i]), 0);
	}
}

void	get_cmds(t_command **cmds, int cmd, char **input)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < cmd)
	{
		j = 0;
		len = ((int)ft_strlen(input[i]));
		while ((input[i][j] == ' ' || input[i][j] == '\t') && j < len)
			j++;
		if (input[i][j] == '(')
		{
			cmds[i]->com = get_strip_str(input[i], 0, len, 0);
			cmds[i]->arg = NULL;
		}
		else
			get_cmd_simple(cmds, input, i, j);
	}
}
