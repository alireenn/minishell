/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:36:17 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/21 17:24:13 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	here_doc_helper(int *fd, char *tmp)
{
	write(fd[1], tmp, ft_strlen(tmp));
	write(fd[1], "\n", 1);
	free(tmp);
	tmp = readline("> ");
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
		tmp = readline("> ");
		while (ft_strlen(tmp) != ft_strlen(end)
			|| ft_strncmp(tmp, end, ft_strlen(end)) != 0)
			here_doc_helper(fd, tmp);
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(NULL);
		return (fd[0]);
	}
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
	while (!special_issep(s[r][i + k + j], " <>") && s[r][i + k + j] != '\0')
		k++;
	if (k == 0)
		return (NULL);
	file = ft_strdup_from_to(s[r], j + i, j + i + k - 1);
	replace(&s[r], j, j + i + k, "\0");
	return (file);
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
			if (special_issep(s[i][j], "><"))
			{
				type = 0;
				file = get_file_io(s, i, j, &type);
				if (file == NULL)
					printf("error");
				cmds[i]->red[type % 2] = 1;
				cmds[i]->fd_red[type % 2] = get_red_io(cmds[i],
						file, type, mini);
			}
			else
				j++;
		}
		i++;
	}
}
