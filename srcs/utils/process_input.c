/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:53:58 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/28 17:40:03 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
#include <termios.h>

void	process_input_aux(t_mini *mini, char *input)
{
	if (input[0] == '\0')
		return ;
	add_history(input);
	process_input(mini, input);
}

int	incomplete_cmd(char *input)
{
	int	i;

	i = (int)ft_strlen(input) - 1;
	while (input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (0);
	else
		return (1);
}

char	*get_other_input(char *input)
{
	char	*tmp;
	char	*ret;

	tmp = readline("> ");
	ret = ft_strjoin(input, tmp);
	free(tmp);
	free(input);
	return (ret);
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
	get_redirs(splitted, mini->commands, mini->cmd, mini);
	expand(splitted, mini);
	get_cmds(mini->commands, mini->cmd, splitted);
	mini->res = execute(mini->tree, mini->commands, mini);
	free_cmds(mini->commands, mini->cmd);
	free_tree(&(mini->tree));
	free_matrix(splitted, mini->cmd);
	free(parsed);
}

char	*our_prompt(int res, t_mini *mini)
{
    struct termios  prev;
    struct termios  new;
	char	*tmp;
	char	*ret;

    if (tcgetattr(STDIN_FILENO, &prev))
        perror("tcgetattr");
    new = prev;
    new.c_lflag &= ~(ECHOCTL);
    if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &new))
        perror("tcsetattr");
	if (res == 1)
	{
		tmp = ft_strjoin("✅ ", "Minishell ➡ ");
		mini->last = 0;
	}
	else
		tmp = ft_strjoin("❌ ", "Minishell ➡ ");
	ret = readline(tmp);
	free(tmp);
    if (tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &prev))
        perror("tcsetattr");
	return (ret);
}
