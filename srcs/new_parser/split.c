/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:15:28 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/18 16:14:21 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

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
			i = search_closing(input, i) - 1;
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
