/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:34:35 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/17 13:05:35 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	replace(char **tbr, int from, int to, char *rep)
{
	char	*before;
	char	*after;
	char	*input;
	char	*ret;

	// printf("to be replaced: |%s|\n", *tbr);
	input = ft_strdup(*tbr);
	before = ft_strdup_from_to(input, 0, from - 1);
	// printf("before: %s\n", before);
	after = ft_strdup(&input[to]);
	// printf("strlen: %d, to: %d\n", (int)ft_strlen(*tbr), to);
	free(input);
	input = ft_strjoin(before, rep);
	ret = ft_strjoin(input, after);
	free(input);
	free(before);
	free(after);
	free(*tbr);
	*tbr = ret;
}

void	emily(int n)
{
	printf("emily %d\n", n);
}
