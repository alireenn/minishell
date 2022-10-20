/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:48:21 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/14 15:41:43 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	remove_quotes_arg(t_command *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (cmd->arg)
	{
		while ((cmd->arg[i] == '\"' || cmd->arg[i] == '\'') && cmd->arg[i] != '\0')
			i++;
		if (i > 0)
		{
			temp = (char *)malloc(sizeof(char) * (int)ft_strlen(cmd->arg) - i + 1);
			if (!temp)
				return ;
			i = 0;
			while (cmd->arg[i])
			{
				if (cmd->arg[i] == '\"' || cmd->arg[i] == '\'')
					i++;
				else
				{
					temp[j] = cmd->arg[i];
					j++;
					i++;
				}
			}
			temp[j] = '\0';
			free (cmd->arg);
			cmd->arg = temp;
		}
	}
}

void	remove_quotes_com(t_command *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (cmd->com)
	{
		while ((cmd->com[i] == '\"' || cmd->com[i] == '\'') && cmd->com[i])
			i++;
		if (i > 0)
		{
			temp = (char *)malloc(sizeof(char *) * (int)ft_strlen(cmd->com) - i + 1);
			i = 0;
			while (cmd->com[i])
			{
				if (cmd->com[i] == '\"' || cmd->com[i] == '\'')
					i++;
				else
				{
					temp[j] = cmd->com[i];
					j++;
					i++;
				}
			}
			temp[j] = '\0';
			free(cmd->com);
			cmd->com = temp;
		}
	}
}
