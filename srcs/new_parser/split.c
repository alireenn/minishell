/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:15:28 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/02 21:49:02 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_syntax(char *in, int i)
{
	int	x;

	x = 1;
	if (in[i + x] == ')')
	{
		printf_fd(2, "minishell: syntax error near unexpected token `)'\n");
		return (0);
	}
	while (i - x >= 0 && (in[i - x] == ' ' || in[i - x] == '\t'))
		x++;
	if (i - x >= 0 && is_sep(in[i - x], "&|p") == 0)
	{
		printf_fd(2, "minishell: syntax error near unexpected token `('\n");
		return (0);
	}
	return (1);
}

int	is_sep(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	strlen_parser(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '&' && input[i + 1] != '\0' && input[i + 1] == '&')
			return (i);
		if (input[i] == '|')
			return (i);
		if (input[i] == '(')
			i = search_closing(input, i, '(', ')') - 1;
		if (input[i] == '\"' || input[i] == '\'')
			i = search_closing(input, i, input[i], input[i]) - 1;
		i++;
	}
	return (i);
}

int	putstr_parser(char *input, int len, int offset, char *matrix)
{
	int	i;

	i = 0;
	while (i < len)
	{
		matrix[i] = input[i + offset];
		i++;
	}
	matrix[i] = '\0';
	while (input[i + offset] == ' '
		|| input[i + offset] == '&' || input[i + offset] == '|')
		i++;
	return (i);
}

char	**split_parser(char *input, int cmd)
{
	char	**matrix;
	int		row;
	int		len;
	int		offset;

	matrix = (char **) malloc (sizeof(char *) * (cmd + 1));
	matrix[cmd] = 0;
	row = 0;
	offset = 0;
	while (row < cmd)
	{
		len = strlen_parser(input + offset);
		matrix[row] = (char *) malloc (sizeof(char) * (len + 1));
		offset += putstr_parser(input, len, offset, matrix[row]);
		row++;
	}
	return (matrix);
}
