/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/19 15:21:10 by gcucino          ###   ########.fr       */
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

void	get_cmds(t_command **cmds, int cmd, char **input)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd)
	{
		j = 0;
		while (input[i][j] == ' ' && j < (int)ft_strlen(input[i]))
			j++;
		if (input[i][j] == '(')
		{
			cmds[i]->com = get_strip_str(input[i], 0, (int)ft_strlen(input[i]));
			cmds[i]->arg = NULL;
		}
		else
		{
			while (input[i][j] != ' ' && j < (int)ft_strlen(input[i]))
				j++;
			cmds[i]->com = get_strip_str(input[i], 0, j);
			while (input[i][j] == ' ')
				j++;
			if (j == (int)ft_strlen(input[i]))
				cmds[i]->arg = NULL;
			else
				cmds[i]->arg = get_strip_str(input[i], j, (int)ft_strlen(input[i]));
		}
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
