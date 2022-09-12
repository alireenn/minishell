/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/12 14:45:37 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/new_parser.h"

int	main(int argc, char **argv)
{
	char		*parsed;
	t_tree		ret;
	char		**splitted;
	t_command	**cmds;
	int			cmd;

	if (argc != 2)
		return (0);
	parsed = parse_tree(argv[1]);
	printf("parsed = %s\n", parsed);
	if (!check_parse(parsed))
		return (1);
	cmd = 0;
	ret = make_tree(parsed, &cmd);
	print_tree(&ret);
	splitted = split_parser(argv[1], cmd);
	cmds = alloc_cmds(cmd);
	int i;
	i = 0;
	while (i < cmd)
	{
		printf("%s\n", splitted[i]);
		i++;
	}
	get_redirs(splitted, cmds, cmd);
	free(parsed);
}
