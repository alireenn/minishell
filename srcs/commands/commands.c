/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:16:49 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/21 17:58:51 by anovelli         ###   ########.fr       */
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

int	get_len_var(char **s, int i, int j)
{
	int	len;

	len = 0;
	while (s[i][j + 1 + len] != '\0' && (s[i][j + 1 + len] != ' '
		&& s[i][j + 1 + len] != '$'))
		len++;
	return (len);
}

void	expand_helper2(char **s, t_env *var_env, int j, int len)
{
	if (var_env != NULL)
		replace(s, j, j + len + 1, var_env->arg_var);
	else
		replace(s, j, j + len + 1, "");
}

int	expand_helper(char **s, int i, int j, t_mini *mini)
{
	int		len;
	int		ret;
	char	*tmp;
	t_env	*var_env;

	len = get_len_var(s, i, j);
	if (len == 0 && s[i][j + 1] == '$')
	{
		replace(&s[i], j, j + 2, "pid");
		ret = 3;
	}
	else if (len == 1 && s[i][j + 1] == '?')
	{
		tmp = ft_itoa(mini->last);
		replace(&s[i], j, j + len + 1, tmp);
		ret = (int)ft_strlen(tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_strdup_from_to(s[i], j + 1, j + len);
		var_env = ft_search_var(mini->env, tmp);
		expand_helper2(&s[i], var_env, j, len);
		ret = (int)ft_strlen(var_env->arg_var);
		free(tmp);
	}
	return (ret);
}

void	expand(char **s, t_mini *mini)
{
	int		i;
	int		j;

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
				j += expand_helper(s, i, j, mini) - 1;
			j++;
		}
		i++;
	}
}

void	get_cmds(t_command **cmds, int cmd, char **input)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd)
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
				cmds[i]->arg = get_strip_str(input[i], j,
						(int)ft_strlen(input[i]));
		}
	}
}
