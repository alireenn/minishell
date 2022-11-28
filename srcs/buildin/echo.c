/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:44:33 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/28 12:11:19 by gcucino          ###   ########.fr       */
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
        //tmp = ft_strdup(com->arg);
		if (flag == 0)
			printf("%s\n", tmp);
		else
			printf("%s", tmp);
		free(tmp);
	}
	com->res = 1;
}

int	check_flag_echo(t_command *cmd)
{
    int i;
    int n;
    int j;

    i = 0;
	if (cmd->arg == NULL)
		return (-1);
    //printf("%s\n", cmd->arg);
	if (cmd->arg[i] == '-')
    {
        while (cmd->arg[i + 1] == 'n')
            i++;
        if (i > 0)
        {
            replace(&cmd->arg, 0, i + 1, "");
            cmd->arg = get_strip_str(cmd->arg, 0, (int)ft_strlen(cmd->arg));
            return (1);
        }
        else
            return (0);
    }
    else if (cmd->arg[0] == '\'' || cmd->arg[0] == '\"')
    {
        while (cmd->arg[i] == cmd->arg[0])
            i++;
        if (cmd->arg[i] != '-')
            return (0);
        n = 1;
        while (cmd->arg[i + n] == 'n')
            n++;
        if (n == 1 || cmd->arg[i + n] != cmd->arg[0])
            return (0);
        j = 0;
        while (cmd->arg[i + n + j] == cmd->arg[0])
            j++;
        if (i == j && (cmd->arg[i + n + j] == ' ' || cmd->arg[i + n + j] == '\0'))
        {
            replace(&cmd->arg, 0, i + n + j, "");
            cmd->arg = get_strip_str(cmd->arg, 0, (int)ft_strlen(cmd->arg));
            return (1);
        }
        return (0);
    }
    else
        return (0);
}
