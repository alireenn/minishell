/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/20 19:11:19 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/new_parser.h"

// void	process_input(t_mini *mini, char *input)
// {
// 	if (input[0] == '\0')
// 		return ;
// 	add_history(input);
// 	mini->tree = make_tree(input, &mini->cmd);
// 	mini->commands = get_cmds(input, mini);
// 	print_tree(&(mini->tree));
// 	print_cmds(mini->commands, mini->cmd);
// 	mini->res = execute(mini->tree, mini->commands, mini);
// 	mini->cmd = 0;
// 	free_cmds(mini->commands, mini->cmd);
// 	free_tree(&(mini->tree));
// }

char	*our_prompt(int res)
{
	char	*tmp;
	char	*ret;

	if (res == 1)
		tmp = ft_strjoin("✅ ", "Minishell ➡ ");
	else
		tmp = ft_strjoin("❌ ", "Minishell ➡ ");
	ret = readline(tmp);
	free(tmp);
	return (ret);
}

void	process_input_aux(t_mini *mini, char *input)
{
	if (input[0] == '\0')
		return ;
	add_history(input);
	process_input(mini, input);
}

void	process_input(t_mini *mini, char *input)
{
	char	*parsed;
	char	**splitted;

	parsed = parse_tree(input);
	if (!check_parse(parsed))
		return ;
	mini->cmd = 0;
	mini->tree = make_tree(parsed, &(mini->cmd));
	splitted = split_parser(input, mini->cmd);
	mini->commands = alloc_cmds(mini->cmd);
	get_redirs(splitted, mini->commands, mini->cmd);
	expand(splitted, mini);
	get_cmds(mini->commands, mini->cmd, splitted);
	mini->res = execute(mini->tree, mini->commands, mini);
	free_cmds(mini->commands, mini->cmd);
	free_tree(&(mini->tree));
	free(parsed);
	free_matrix(splitted, mini->cmd);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	char	*prompt;

	if (argc > 1)
		return (printf("Minishell: %s: No such file or directory\n", argv[1]));
	(void)argc;
	(void)argv;
	// signal(SIGINT, received);
	// signal(SIGQUIT, quit);
	mini = init_mini(envp);
	prompt = our_prompt(mini->res);
	while (prompt != NULL)
	{
		process_input_aux(mini, prompt);
		free(prompt);
		if (mini->exit == 1)
			break ;
		prompt = our_prompt(mini->res);
	}
	free_mini(mini);
}
