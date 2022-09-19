/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:34:35 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 17:05:04 by gcucino          ###   ########.fr       */
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
	// printf("%s\n", ret);
	free(input);
	free(before);
	free(after);
	free(*tbr);
	*tbr = ret;
}

int	equal_strings(char *com, char *exec)
{
	int	len_com;
	int	len_exec;

	len_com = (int)ft_strlen(com);
	len_exec = (int)ft_strlen(exec);
	if (len_com == len_exec && ft_strncmp(com, exec, len_com) == 0)
		return (0);
	else
		return (1);
}

char	*ft_join_char(char *s1, char *s2, char c)
{
	char	*tmp;
	char	*ret;
	char	ch[2];

	ch[0] = c;
	ch[1] = '\0';
	tmp = ft_strjoin(s1, ch);
	ret = ft_strjoin(tmp, s2);
	free(tmp);
	return (ret);
}

char	*get_strip_str(char *input, int from, int to)
{
	int	i;
	int	j;

	i = 0;
	while (input[from + i] == ' ')
		i++;
	j = 0;
	while (input[to - 1 - j] == ' ')
		j++;
	return (ft_strdup_from_to(input, from + i, to - j - 1));
}
