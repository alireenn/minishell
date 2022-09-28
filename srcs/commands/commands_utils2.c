/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:48:21 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/28 15:05:36 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

void	remove_quotes_arg(t_command *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (cmd->arg[i] == '\"')
		i++;
	temp = (char *)malloc(sizeof(char *) * (int)ft_strlen(cmd->arg) - i + 1);
	i = 0;
	while (cmd->arg[i])
	{
		if (cmd->arg[i] == '\"')
			i++;
		else
		{
			temp[j] = cmd->arg[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	cmd->arg = temp;
	// free(temp);
}

void	remove_quotes_com(t_command *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (cmd->com[i] == '\"')
		i++;
	temp = (char *)malloc(sizeof(char *) * (int)ft_strlen(cmd->com) - i + 1);
	i = 0;
	while (cmd->com[i])
	{
		if (cmd->com[i] == '\"')
			i++;
		else
		{
			temp[j] = cmd->com[i];
			j++;
			i++;
		}
	}
	temp[j] = '\0';
	cmd->com = temp;
	// free(temp);
}
