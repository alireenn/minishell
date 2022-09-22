/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/22 16:25:49 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

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

void	get_cmd_simple(t_command **cmds, char **input, int i, int j)
{
	while (input[i][j] != ' ' && j < (int)ft_strlen(input[i]))
		j++;
	cmds[i]->com = get_strip_str(input[i], 0, j);
	while (input[i][j] == ' ')
		j++;
	if (j == (int)ft_strlen(input[i]))
		cmds[i]->arg = NULL;
	else
		cmds[i]->arg = get_strip_str(input[i], j, (int)ft_strlen(input[i]));
}

void	get_cmds(t_command **cmds, int cmd, char **input)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd)
	{
		j = 0;
		while (input[i][j] == ' ' && j < (int)ft_strlen(input[i]))
			j++;
		if (input[i][j] == '(')
		{
			cmds[i]->com = get_strip_str(input[i], 0, (int)ft_strlen(input[i]));
			cmds[i]->arg = NULL;
		}
		else
			get_cmd_simple(cmds, input, i, j);
	}
}
