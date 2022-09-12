/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:20:10 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/12 16:07:04 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

// 1 -> '>'

// void	get_red_input(char *s, t_command *cmds, int j, int flag)
// {
	
// }

void	get_redirs(char **s, t_command **cmds, int cmd)
{
	int		i;
	int		j;
	int		a;
	char	**save;

	i = 0;
	a = 0;
	while (i < cmd) //cmd e'il numero di comandi che nellésempio di prima era 3
	{
		if (s[i][j] == '>' && s[i][j + 1] != '\0' && s[i][j + 1] == '>')
		{
			save = ft_split(s[i], ">", &a);
			printf("%s\n", save[1]);			
			// get_red_input(save[1], cmds, );

		}
		j = 0;
		cmds++;
		// j = 0;
		// while (j < (int)strlen(s[i]))
		// {
		// 	if (s[i][j] == '>' && s[i][j + 1] != '\0' && s[i][j + 1] != '>')
		// 	{
		// 		get_red_input(s[i], cmds[i], j, 1);
		// 	}
		// 	else if ()
		// 	j++;
		// }
		i++;
	}
	while (i < cmd)
	{
		printf("%s\n", s[i]);
		i++;
	}
}
