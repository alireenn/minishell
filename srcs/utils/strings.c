/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:34:35 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/23 18:14:18 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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
	while (input[from + i] == ' ' && input[from + i] != '\0')
		i++;
	if (from + i == (int)ft_strlen(input))
		return (NULL);
	j = 0;
	while (input[to - 1 - j] == ' ')
		j++;
	return (ft_strdup_from_to(input, from + i, to - j - 1));
}

char	*get_strip_str_q(char *input, int from, int to)
{
	int	i;
	int	j;

	i = 0;
	while (input[from + i] == ' ' && input[from + i] != '\0' && input[from + i] != '\'' && input[from + i] != '\"')
		i++;
	if (input[from + i] == '\'' || input[from + i] == '\"')
		i++;
	if (from + i == (int)ft_strlen(input))
		return (NULL);
	j = 0;
	while (input[to - 1 - j] == ' ' && input[to - 1 - j] != '\'' && input[to - 1 - j] != '\"')
		j++;
	if (input[to - 1 - j] == '\'' || input[to - 1 - j] == '\"')
		j++;
	return (ft_strdup_from_to(input, from + i, to - j - 1));
}

void	replace(char **tbr, int from, int to, char *rep)
{
	char	*before;
	char	*after;
	char	*input;
	char	*ret;

	input = ft_strdup(*tbr);
	before = ft_strdup_from_to(input, 0, from - 1);
	after = ft_strdup(&input[to]);
	free(input);
	input = ft_strjoin(before, rep);
	ret = ft_strjoin(input, after);
	free(input);
	free(before);
	free(after);
	free(*tbr);
	*tbr = ret;
}
