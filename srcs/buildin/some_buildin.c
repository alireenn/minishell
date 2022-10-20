/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:52 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/13 20:09:59 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	int	j;

	j = 0;
	i = 0;
	if (cmd->arg == NULL)
		return (-1);
	while (cmd->arg[i] != '\0')
	{
		if (cmd->arg[i] == '-')
		{
			j = 1;
			while (cmd->arg[i + j] == 'n')
				j++;
			if (cmd->arg[i + j] == ' ')
			{
				replace(&cmd->arg, i, i + j + 1, "");
				cmd->arg = get_strip_str(cmd->arg, 0, (int)ft_strlen(cmd->arg));
			}
			else
				return (0);
			return (1);
		}
		i++;
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

void	ft_exit(t_mini *mini, t_command *com)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	mini->exit = 1;
	com->res = 1;
	if (com->arg != NULL)
	{
		while (com->arg[i] >= '0' && com->arg[i] <= '9')
			i++;
		if (i < (int)ft_strlen(com->arg) && com->arg[i] != ' ')
		{
			printf_fd(2, "minishell: exit: %s: numeric argument required\n",
				com->arg);
			mini->last = 255;
		}
		else if (i < (int)ft_strlen(com->arg) && com->arg[i] == ' ')
		{
			printf_fd(2, "minishell: exit: too many arguments\n");
			mini->last = 1;
		}
		else
			mini->last = ft_atoi(com->arg);
	}
}
