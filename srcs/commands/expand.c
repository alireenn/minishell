/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:25:53 by gcucino           #+#    #+#             */
/*   Updated: 2022/12/05 18:00:08 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	check_env_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	while (var[i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	expand(char **s, t_mini *mini)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	if (s[i] == NULL)
		return ;
	while (s[i] != NULL)
	{
		j = 0;
		while (j < (int)ft_strlen(s[i]))
		{
			if (s[i][j] == '\"')
				flag = !flag;
			if (s[i][j] == '\'' && flag == 0)
				j = search_closing(s[i], j, s[i][j], s[i][j]) - 1;
			if (s[i][j] == '$'
			&& s[i][j + 1] != '\0' && s[i][j + 1] != ' ')
				j += expand_helper(s, i, j, mini) - 1;
			else
				j++;
		}
		i++;
	}
}

int	get_len_var(char **s, int i, int j)
{
	int	len;

	len = 0;
	if (ft_isdigit(s[i][j + 1 + len]))
		return (1);
	while (s[i][j + 1 + len] != '\0' && (s[i][j + 1 + len] != ' '
		&& s[i][j + 1 + len] != '$' && s[i][j + 1 + len] != '('
		&& s[i][j + 1 + len] != ')' && s[i][j + 1 + len] != '"'
		&& s[i][j + 1 + len] != '\''))
		len++;
	return (len);
}

int	expand_helper2(char **s, t_mini *mini, int j, int len)
{
	int		ret;
	char	*tmp;
	t_env	*var_env;

	ret = 1;
	tmp = ft_strdup_from_to(*s, j + 1, j + len);
	printf("tmp: %s\n", tmp);
	if (check_env_var(tmp) != 0)
	{
		var_env = ft_search_var(mini->env, tmp);
		if (var_env != NULL)
		{
			replace(s, j, j + len + 1, var_env->arg_var);
			printf("%s\n", var_env->arg_var);
			ret = (int)ft_strlen(var_env->arg_var);
		}	
		else
			replace(s, j, j + len + 1, "");
	}
	free(tmp);
	return (ret);
}

int	expand_helper(char **s, int i, int j, t_mini *mini)
{
	int		len;
	int		ret;
	char	*tmp;

	len = get_len_var(s, i, j);
	printf("%s, %d\n", *s, len);
	if (len == 0 && s[i][j + 1] == '$')
	{
		replace(&s[i], j, j + 2, mini->pid);
		ret = (int)ft_strlen(mini->pid);
	}
	else if (len == 1 && s[i][j + 1] == '?')
	{
		tmp = ft_itoa(mini->last);
		replace(&s[i], j, j + len + 1, tmp);
		ret = (int)ft_strlen(tmp);
		free(tmp);
	}
	else if (len == 1 && s[i][j + 1] == '0')
	{
		replace(&s[i], j, j + 2, "minishell");
		ret = 9;
	}
	else
		ret = expand_helper2(&s[i], mini, j, len);
	return (ret);
}
