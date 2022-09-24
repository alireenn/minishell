/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:25:53 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/24 18:04:19 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

int	get_len_var(char **s, int i, int j)
{
	int	len;

	len = 0;
	while (s[i][j + 1 + len] != '\0' && (s[i][j + 1 + len] != ' '
		&& s[i][j + 1 + len] != '$' && s[i][j + 1 + len] != '('
		&& s[i][j + 1 + len] != ')' && s[i][j + 1 + len] != '\"'))
		len++;
	return (len);
}

int	expand_helper2(char **s, t_mini *mini, int j, int len)
{
	int		ret;
	char	*tmp;
	t_env	*var_env;

	ret = 0;
	tmp = ft_strdup_from_to(*s, j + 1, j + len);
	var_env = ft_search_var(mini->env, tmp);
	if (var_env != NULL)
	{
		replace(s, j, j + len + 1, var_env->arg_var);
		ret = (int)ft_strlen(var_env->arg_var);
	}	
	else
		replace(s, j, j + len + 1, "");
	free(tmp);
	return (ret);
}

int	expand_helper(char **s, int i, int j, t_mini *mini)
{
	int		len;
	int		ret;
	char	*tmp;

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
		ret = expand_helper2(&s[i], mini, j, len);
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
			if (s[i][j] == '\'')
				j = search_closing(s[i], j, s[i][j], s[i][j]) - 1;
			if (s[i][j] == '$'
			&& s[i][j + 1] != '\0' && s[i][j + 1] != ' ')
				j += expand_helper(s, i, j, mini) - 1;
			j++;
		}
		i++;
	}
}
