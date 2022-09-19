/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:52 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/19 15:47:54 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

void	ft_pwd(t_command *cmd)
{
	char	pwd[PATH_MAX];
	int		i;

	i = 0;
	getcwd(pwd, PATH_MAX);
	while (pwd[i])
	{
		write(1, &pwd[i], 1);
		i++;
	}
	write(1, "\n", 1);
	cmd->res = 1;
}

int	check_flag_echo(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg == NULL)
		return (-1);
	if (cmd->arg[i] == '-' && cmd->arg[i + 1] == 'n' && cmd->arg[i + 2] == ' ')
	{
		i = 2;
		while (cmd->arg[i] == ' ')
			i++;
		replace(&cmd->arg, 0, i - 1, "");
		return (1);
	}
	return (0);
}

int	check_par(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(' || str[i] == ')'
			|| (str[i] == '(' && str[i + 1] == ')'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(char *str, t_command *com)
{
	int	flag;

	flag = check_flag_echo(com);
	if (str == NULL)
		printf_fd(1, "\n");
	else
	{
		if (flag == 0)
		{	
			ft_putstr_fd(com->arg, 1);
			write(1, "\n", 1);
		}
		else
			ft_putstr_fd(com->arg, 1);
	}
	com->res = 1;
}

void	ft_exit(t_mini *mini, t_command *com)
{
	ft_putstr_fd("exit\n", 1);
	mini->exit = 1;
	com->res = 1;
}
