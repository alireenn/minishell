/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:35:13 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/20 16:56:26 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	ft_cd(t_mini *mini, char *arg, t_command *com)
{
	char	*tmp;
	t_env	*home;

	if (arg == NULL)
	{
		home = ft_search_var(mini->env, "HOME");
		if (home == NULL)
		{
			ft_cd_supp2(mini, com);
			return ;
		}
		tmp = ft_strdup(home->arg_var);
	}
	else
		tmp = ft_join_char(mini->pwd, arg, '/');
	if (chdir(tmp) == -1)
	{
		ft_cd_supp(tmp, mini, com, arg);
		return ;
	}
	free(mini->pwd);
	com->res = 1;
	mini->pwd = tmp;
	return ;
}

void	ft_cd_supp2(t_mini *mini, t_command *com)
{
	printf_fd(2, "minishell: cd: HOME not set\n");
	mini->last = 1;
	com->res = 0;
}

void	ft_cd_supp(char *tmp, t_mini *mini, t_command *com, char *arg)
{
	printf_fd(2, "minishell: cd: %s: No such file or directory\n", arg);
	free(tmp);
	mini->last = 1;
	com->res = 0;
	return ;
}
