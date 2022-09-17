/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/17 12:34:51 by gcucino          ###   ########.fr       */
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

void	process_input(t_mini *mini, char *input)
{
	char	*parsed;
	char	**splitted;

	if (input[0] == '\0')
		return ;
	//add_history(input);
	parsed = parse_tree(input);
	printf("parsed = %s\n", parsed);
	if (!check_parse(parsed))
		return ;
	mini->cmd = 0;
	mini->tree = make_tree(parsed, &(mini->cmd));
	print_tree(&(mini->tree));
	splitted = split_parser(input, mini->cmd);
	mini->commands = alloc_cmds(mini->cmd);
	get_redirs(splitted, mini->commands, mini->cmd);
	int	i = 0;
	while (i < mini->cmd)
	{
		printf("%s\n", splitted[i]);
		i++; 
	}
	/* mini->res = execute(mini->tree, mini->commands, mini);
	mini->cmd = 0;
	free_cmds(mini->commands, mini->cmd);
	free_tree(&(mini->tree));*/
}

int	main(int argc, char **argv, char **envp)
{
	t_mini		*mini;

	if (argc != 2)
		return (0);
	mini = init_mini(envp);
	process_input(mini, argv[1]);
}
