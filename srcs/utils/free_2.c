/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:56:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/01 12:01:31 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_subshell(t_mini *mini2, char **envp2, char	*new_cmd)
{
	free_mini(mini2);
	free_matrix_no_rows(envp2);
	free(new_cmd);
}

int	free_mini(t_mini *mini)
{
	int	ret;

	ret = mini->last;
	if (mini->env != NULL)
		free_env(mini->env);
	if (mini->secret != NULL)
		free_env(mini->secret);
	if (mini->pwd != NULL)
		free(mini->pwd);
	close(mini->save_in);
	close(mini->save_out);
	free(mini);
	return (ret);
}
