/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:25:42 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/18 15:50:19 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

void	split_at(char *input, t_env *env, char c)
{
	int		i;
	int		j;

	i = 0;
	while (input[i] != '\0' && input[i] != c)
		i++;
	j = 0;
	env->name_var = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		env->name_var[j] = input[j];
		j++;
	}
	env->name_var[j] = '\0';
	if (input[i] == '\0')
		env->arg_var = NULL;
	else
		env->arg_var = ft_strdup(&input[i + 1]);
	env->next = NULL;
}

t_env	*copy_env(t_mini *mini, int *n)
{
	int		i;
	t_env	*it;
	t_env	*ret;
	t_env	*new;
	t_env	*tmp;

	it = mini->env;
	i = 1;
	tmp = malloc(sizeof(t_env));
	tmp->name_var = ft_strdup(it->name_var);
	tmp->arg_var = ft_strdup(it->arg_var);
	tmp->next = NULL;
	ret = tmp;
	it = it->next;
	while (it != NULL)
	{
		new = malloc(sizeof(t_env));
		new->name_var = ft_strdup(it->name_var);
		new->arg_var = ft_strdup(it->arg_var);
		new->next = NULL;
		tmp->next = new;
		tmp = new;
		it = it->next;
		i++;
	}
	(*n) = i;
	return (ret);
}

t_env	*ft_search_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(name) == ft_strlen(tmp->name_var)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
