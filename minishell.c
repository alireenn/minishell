/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/30 15:46:47 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

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

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handle);
}

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
		process_input_aux(mini, prompt);
		free(prompt);
		if (mini->exit == 1)
			break ;
		prompt = our_prompt(mini->res, mini);
	}
	ret = free_mini(mini);
	return (ret);
}
