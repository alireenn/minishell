/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:43:29 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/20 16:45:25 by anovelli         ###   ########.fr       */
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
