/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:20:10 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 15:33:59 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

// 1 -> '>'

char	*get_file_io(char **s, int r, int j, int *type)
{
	int		i;
	int		k;
	char	*file;

	i = 0;
	k = 0;
	(*type) = (s[r][j] == '>') + 2 * (s[r][j] == '<')
		+ 2 * (s[r][j + 1] == '<') + 2 * (s[r][j + 1] == '>');
	if (s[r][j] == s[r][i + j + 1])
		i++;
	i++;
	while (s[r][i + j] == ' ')
		i++;
	while (!special_issep(s[r][i + k + j], " <>") && s[r][i + k + j] != '\0')
		k++;
	if (k == 0)
		return (NULL);
	file = ft_strdup_from_to(s[r], j + i, j + i + k);
	replace(&s[r], j, j + i + k, "");
	return (file);
}

void	get_redirs(char **s, t_command **cmds, int cmd)
{
	int		i;
	int		j;
	char	*file;
	int		type;

	i = 0;
	while (i < cmd)
	{
		j = 0;
		while (j < (int)ft_strlen(s[i]))
		{
			if (special_issep(s[i][j], "><"))
			{
				type = 0;
				file = get_file_io(s, i, j, &type);
				if (file == NULL)
					printf("error");
				get_red_io(cmds[i], type);
			}
			j++;
		}
		cmds++;
		i++;
	}
}
