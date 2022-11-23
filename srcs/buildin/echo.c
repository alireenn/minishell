/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:44:33 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/23 12:55:09 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str, t_command *com)
{
	int		flag;
	char	*tmp;

	if (!com->arg)
	{
		printf_fd(1, "\n");
		return ;
	}
	flag = check_flag_echo(com);
	if (str == NULL)
		printf_fd(1, "\n");
	else
	{
		tmp = remove_quotes_str(com->arg);
		if (flag == 0)
			printf("%s\n", tmp);
		else
			printf("%s", tmp);
		free(tmp);
	}
	com->res = 1;
}

int	flag_echo_help(t_command *cmd, int i)
{
	int	j;
	
	j = 1;
	while (cmd->arg[i + j] == 'n')
		j++;
	if (cmd->arg[i + j] == ' ' && j > 1)
	{
		replace(&cmd->arg, i, i + j + 1, "");
		cmd->arg = get_strip_str(cmd->arg, 0, (int)ft_strlen(cmd->arg));
		return (1);
	}
	return (0);
}

int	check_flag_echo(t_command *cmd)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	if (cmd->arg == NULL)
		return (-1);
	while (cmd->arg[i] != '\0')
	{
		if (cmd->arg[i] == '\'' || cmd->arg[i] == '\"')
			i = search_closing(cmd->arg, i, cmd->arg[i], cmd->arg[i]);
		if (cmd->arg[i] == '-')
		{
			if (flag_echo_help(cmd, i) == 1)
			{
				ret = 1;
				i = -1;
			}
			else
				return (ret);
		}
		i++;
	}
	return (ret);
}
