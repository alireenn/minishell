/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:44:33 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/10 15:46:09 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *str, t_command *com)
{
	int		flag;

	if (!com->arg)
	{
		printf_fd(1, "\n");
		return ;
	}
	remove_quotes_arg(com);
	flag = check_flag_echo(com);
	if (str == NULL)
		printf_fd(1, "\n");
	else
	{
		if (flag == 0)
			printf("%s\n", com->arg);
		else
			printf("%s", com->arg);
	}
	com->res = 1;
}

int	flag_echo_help(t_command *cmd, int i, int j)
{
	j = 1;
	while (cmd->arg[i + j] == 'n')
		j++;
	if (cmd->arg[i + j] == ' ')
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
	int	j;

	j = 0;
	i = 0;
	if (cmd->arg == NULL)
		return (-1);
	while (cmd->arg[i] != '\0')
	{
		if (cmd->arg[i] == '-')
		{
			if (flag_echo_help(cmd, i, j) == 1)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
