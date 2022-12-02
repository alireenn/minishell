/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/02 21:55:20 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_mini	*mini;
	char	*prompt;

	if (argc > 1)
		return (printf("Minishell: %s: No such file or directory\n", argv[1]));
	ft_sig();
	mini = init_mini(envp);
	my_pid(mini);
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
		prompt = our_prompt(mini->res, mini);
	}
	ret = free_mini(mini);
	return (ret);
}
