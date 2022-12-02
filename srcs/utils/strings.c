/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:34:35 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/02 12:36:56 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	mod_strlen(char *str, char *charset, char *avoid)
{
	int	i;
	int	len;
	int	open;

	i = 0;
	len = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{
				open = mod_helper(str, i, avoid, open);
				if (is_sep(str[i], charset) == 1 && open == 0)
					break ;
				i++;
				len++;
			}
			return (len);
		}
		else
			i++;
	}
	return (0);
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

char	*get_strip_str(char *input, int from, int to, int flag)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	if (input == NULL)
		return (NULL);
	while ((input[from + i] == '\t' || input[from + i] == ' ')
		&& input[from + i] != '\0')
		i++;
	if (from + i == (int)ft_strlen(input))
	{
		if (flag == 1)
			free(input);
		return (NULL);
	}
	j = 0;
	while (input[to - 1 - j] == ' ' || input[to - 1 - j] == '\t')
		j++;
	ret = ft_strdup_from_to(input, from + i, to - j - 1);
	if (flag == 1)
		free(input);
	return (ret);
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
