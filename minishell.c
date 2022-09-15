/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/15 17:28:39 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/new_parser.h"

void	process_input(t_mini *mini, char *input)
{
	if (input[0] == '\0')
		return ;
	add_history(input);
	mini->tree = make_tree(input, &mini->cmd);
	mini->commands = get_cmds(input, mini);
	print_tree(&(mini->tree));
	print_cmds(mini->commands, mini->cmd);
	mini->res = execute(mini->tree, mini->commands, mini);
	mini->cmd = 0;
	free_cmds(mini->commands, mini->cmd);
	free_tree(&(mini->tree));
}

void	init_mini(t_mini *mini, char **envp)
{
	mini->exit = 0;
	init_env(mini, envp);
	mini->secret = NULL;
	init_secret_env(mini);
	mini->pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(mini->pwd, PATH_MAX);
	mini->save_out = dup(STDOUT_FILENO);
	mini->save_in = dup(STDIN_FILENO);
	mini->tree = NULL;
	mini->last = 0;
	mini->res = 1;
	mini->cmd = 0;
}

int	main(int argc, char **argv)
{
	char		*parsed;
	t_tree		ret;
	char		**splitted;
	t_command	**cmds;
	int			cmd;

	if (argc != 2)
		return (0);
	parsed = parse_tree(argv[1]);
	printf("parsed = %s\n", parsed);
	if (!check_parse(parsed))
		return (1);
	cmd = 0;
	ret = make_tree(parsed, &cmd);
	print_tree(&ret);
	splitted = split_parser(argv[1], cmd);
	cmds = alloc_cmds(cmd);
	// expand()
	get_redirs(splitted, cmds, cmd);
	int i = 0;
	init_mini(mini, envp);
	process_input(mini, prompt);
	while (i < cmd)
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	free(parsed);
}
