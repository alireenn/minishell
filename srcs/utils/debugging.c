/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:02:22 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 18:29:43 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	print_cmds(t_command **cmds, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		if (cmds[i]->com != NULL)
			printf("comando: $%s$\n", cmds[i]->com);
		if (cmds[i]->arg != NULL)
			printf("argomento: $%s$\n", cmds[i]->arg);
		i++;
	}
}

void	emily(int n)
{
	printf("emily %d\n", n);
}