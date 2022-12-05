/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/05 11:50:55 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_mini	*mini;
	char	*prompt;

	if (argc > 1)
		return (printf_fd(2, "Minishell: %s: No such file or directory\n", argv[1]));
	ft_sig();
	mini = init_mini(envp);
	mini->pid = "emily";
	//my_pid(mini);
	prompt = our_prompt(mini->res, mini);
	while (prompt != NULL)
	{
		while (incomplete_cmd(prompt) == 0)
			prompt = get_other_input(prompt);
		if (prompt)
		{
			process_input_aux(mini, prompt);
			free(prompt);
		}
		if (mini->exit == 1)
			break ;
		rl_already_prompted = 0;
		prompt = our_prompt(mini->res, mini);
	}
	ret = free_mini(mini);
	return (ret);
}
