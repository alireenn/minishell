/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/17 17:38:10 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

t_command	**alloc_cmds(int cmd)
{
	t_command	**cmds;
	int			j;

	cmds = malloc (sizeof(t_command *) * cmd);
	j = 0;
	while (j < cmd)
	{
		cmds[j] = malloc(sizeof(t_command));
		j++;
	}
	return (cmds);
}

void	expand(char **s, t_mini *mini)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	t_env	*var_env;

	i = 0;
	if (s[i] == NULL)
		return ;
	while (s[i] != NULL)
	{
		j = 0;
		while (j < (int)ft_strlen(s[i]))
		{
			if (s[i][j] == '$'
			&& s[i][j + 1] != '\0' && s[i][j + 1] != ' ')
			{
				len = 0;
				while (s[i][j + 1 + len] != '\0' && (s[i][j + 1 + len] != ' '
					&& s[i][j + 1 + len] != '$'))
					len++;
				if (len == 0 && s[i][j + 1] == '$')
				{
					replace(&s[i], j, j + 2, "pid");
					j++;
				}
				else if (len == 1 && s[i][j + 1] == '?')
				{
					tmp = ft_itoa(mini->last);
					replace(&s[i], j, j + len + 1, tmp);
					free(tmp);
				}
				else
				{
					tmp = ft_strdup_from_to(s[i], j + 1, j + len);
					var_env = ft_search_var(mini->env, tmp);
					if (var_env != NULL)
						replace(&s[i], j, j + len + 1, var_env->arg_var);
					else
						replace(&s[i], j, j + len + 1, "");
					free(tmp);
				}
			}
			j++;
		}
		i++;
	}
}

void	get_cmds(t_command **cmds, int cmd, char **input)
{
	int	i;
	int	j;
	int	k;
	int	z;

	i = 0;
	while (i < cmd)
	{
		j = 0;
		z = 0;
		if (input[i][j] == '(')
			j = (int)ft_strlen(input[i]);
		while (j < (int)ft_strlen(input[i]) && input[i][j + z] == ' ')
			z++;
		while (j < (int)ft_strlen(input[i]) && input[i][j + z] != ' ')
			j++;
		k = 0;
		while (input[i][j - 1 - k + z] == ' ' && j - 1 - k > 0)
			k++;
		cmds[i]->com = ft_strdup_from_to(input[i], z, j - 1 - k + z);
		printf("cmd = |%s|\n", cmds[i]->com);
		j += z;
		while (input[i][j] != '\0' && input[i][j] == ' ')
			j++;
		if (j != (int)ft_strlen(input[i]))
		{
			k = (int)ft_strlen(input[i]);
			while (input[i][k - 1] == ' ')
				k--;
			cmds[i]->arg = ft_strdup_from_to(input[i], j, k - 1);
		}
		else
			cmds[i]->arg = NULL;
		printf("arg = |%s|\n", cmds[i]->arg);
		i++;
	}
}

void	free_cmds(t_command	**cmds, int cmd)
{
	int	i;

	i = 0;
	while (i < cmd)
	{
		if (cmds[i]->com != NULL)
			free(cmds[i]->com);
		if (cmds[i]->arg != NULL)
			free(cmds[i]->arg);
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
