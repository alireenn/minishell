/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:43:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/21 15:50:16 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

int	check_parse(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i] != '\0')
	{
		if (parsed[i] == '>' && parsed[i + 1] == '(')
		{
			printf("minishell: parse error near `)'\n");
			return (0);
		}
		else if (parsed[i] == '>' && parsed[i + 1] == '<')
		{
			printf("minishell: syntax error near unexpected token `<'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*parse_tree_helper(char *input, char *ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (special_issep(input[i], "()<>"))
		{
			ret[j] = input[i];
			j++;
		}
		if (special_issep(input[i], "&|")
			&& input[i + 1] != '\0' && input[i + 1] == input[i])
		{
			ret[j] = input[i];
			i++;
			j++;
		}
		else if (input[i] == '|' && input[i + 1] != '\0' && input[i + 1] != '&')
		{
			ret[j] = 'p';
			i++;
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
