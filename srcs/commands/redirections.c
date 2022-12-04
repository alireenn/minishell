/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:17 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/30 19:14:28 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*here_doc_helper(int *fd, char *tmp)
{
	write(fd[1], tmp, ft_strlen(tmp));
	write(fd[1], "\n", 1);
	free(tmp);
	rl_already_prompted = 0;
	tmp = readline("> ");
	rl_already_prompted = 1;
	return (tmp);
}

char	*get_file_io(char **s, int r, int j, int *type)
{
	int		i;
	int		k;
	char	*file;

	i = 0;
	k = 0;
	(*type) = (s[r][j] == '>') + 2 * (s[r][j] == '<')
		+ 2 * (s[r][j + 1] == '<') + 2 * (s[r][j + 1] == '>');
	if (s[r][j] == s[r][i + j + 1])
		i++;
	i++;
	while (s[r][i + j] == ' ')
		i++;
	while (!is_sep(s[r][i + k + j], " <>") && s[r][i + k + j] != '\0')
		k++;
	if (k == 0)
		return (NULL);
	file = ft_strdup_from_to(s[r], j + i, j + i + k - 1);
	replace(&s[r], j, j + i + k, "\0");
	return (file);
}

void	get_redirs_type(char *file, t_mini *mini, t_command *cmd, int type)
{
	if (file == NULL)
	{
		printf("error");
		return ;
	}
	cmd->red[type % 2] = 1;
	cmd->fd_red[type % 2] = get_red_io(cmd,
			file, type, mini);
}

void	get_redirs(char **s, t_command **cmds, int cmd, t_mini *mini)
{
	int		i;
	int		j;
	char	*file;
	int		type;

	i = 0;
	while (i < cmd)
	{
		j = 0;
		while (j < (int)ft_strlen(s[i]))
		{
			if (is_sep(s[i][j], "\'\""))
				j = search_closing(s[i], j, s[i][j], s[i][j]) - 1;
			if (is_sep(s[i][j], "><"))
			{
				file = get_file_io(s, i, j, &type);
				get_redirs_type(file, mini, cmds[i], type);
				free(file);
			}
			else
				j++;
		}
		i++;
	}
}

int	get_red_io(t_command *cmd, char *filename, int type, t_mini *mini)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (type == 1)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode));
	else if (type == 2)
	{
		if (access(filename, F_OK) != 0)
		{
			printf("minishell: %s: No such file or directory\n", filename);
			mini->last = 1;
			cmd->res = 0;
			return (-1);
		}
		return (open(filename, O_RDONLY | O_CREAT, mode));
	}
	else if (type == 3)
		return (open(filename, O_WRONLY | O_CREAT | O_APPEND, mode));
	else
		return (here_doc(filename));
}
