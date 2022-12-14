/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_buildin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 12:50:52 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/02 20:43:19 by gcucino          ###   ########.fr       */
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
