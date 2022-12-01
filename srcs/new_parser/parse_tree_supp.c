/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:43:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/01 12:37:17 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_redirs(int i, char *parsed)
{
	if (parsed[i] == '>' && parsed[i + 1] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		return (0);
	}
	else if (parsed[i] == '<' && parsed[i + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	check_parenthesis(char *input)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (input[i] != 0)
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = search_closing(input, i, input[i], input[i]);
		if (input[i] == ')')
			open--;
		else if (input[i] == '(')
			open++;
		i++;
	}
	return (open);
}

int	check_parse(char *parsed)
{
	int	i;

	i = 0;
	if (check_parenthesis(parsed) != 0)
		return (0);
	while (parsed[i] != '\0')
	{
		if (parsed[i] == '>' && parsed[i + 1] == '(')
		{
			printf("minishell: parse error near `)'\n");
			return (0);
		}
		if (check_redirs(i, parsed) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	put_symbols(char *in, char *ret, int *i, int *j)
{
	if (is_sep(in[(*i)], "\"\'"))
		*(i) = search_closing(in, (*i), in[(*i)], in[(*i)]);
	if (is_sep(in[(*i)], "()<>"))
	{
		ret[(*j)] = in[(*i)];
		(*j)++;
	}
	if (is_sep(in[(*i)], "&|") && in[(*i) + 1] != '\0'
		&& in[(*i) + 1] == in[(*i)])
	{
		ret[(*j)] = in[(*i)];
		(*i)++;
		(*j)++;
	}
	else if (in[(*i)] == '|' && in[(*i) + 1] != '\0' && in[(*i) + 1] != '&')
	{
		ret[(*j)] = 'p';
		(*i)++;
		(*j)++;
	}
}

char	*parse_tree_helper(char *in, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (in[i] != '\0')
	{
		put_symbols(in, ret, &i, &j);
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
