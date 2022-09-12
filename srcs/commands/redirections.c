/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:20:10 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/11 18:10:02 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	get_redirs(char **s, t_command **cmds, int cmd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd)
	{
		j = 0;
		while (j < strlen(s[i]))
		{
			j++;
		}
		i++;
	}
}
