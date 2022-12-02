/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:53:58 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/02 20:08:47 by gcucino          ###   ########.fr       */
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

	if (input == NULL)
		return (1);
	i = (int)ft_strlen(input) - 1;
	while (input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (0);
	if (check_parenthesis(input) > 0)
		return (0);
	else
	{
		i = 0;
		while (input[i] != 0)
		{
			if (input[i] == '\'' || input[i] == '\"')
				i = search_closing(input, i, input[i], input[i]);
			i++;
		}
		return (1);
	}
}

char	*get_other_input(char *input)
{
	char	*tmp;
	char	*ret;

	tmp = readline("> ");
	if (!tmp)
	{
		printf_fd(2, "minishell: syntax error: unexpected end of file\n");
		free(input);
		return (NULL);
	}
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
	if (parsed == NULL || !check_parse(parsed))
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
	struct termios	prev;
	struct termios	new;
	char			*tmp;
	char			*ret;

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
