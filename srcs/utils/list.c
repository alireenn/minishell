/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:32 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/11 17:58:13 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	delete_elem(t_env **list, t_env *elem)
{
	t_env	*it;

	it = (*list);
	if (*list == elem)
		(*list) = (*list)->next;
	else
	{
		while (it->next != elem)
			it = it->next;
		it->next = elem->next;
	}
	free(elem->name_var);
	free(elem->arg_var);
	free(elem);
}

t_env	*create_elem(char *elem_name, char *elem_arg)
{
	t_env	*ret;

	ret = (t_env *) malloc (sizeof(t_env));
	ret->name_var = ft_strdup(elem_name);
	if (elem_arg != NULL)
		ret->arg_var = ft_strdup(elem_arg);
	else
		ret->arg_var = NULL;
	ret->next = NULL;
	return (ret);
}

void	change_var(t_env *env, char *name, char *arg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->name_var) == ft_strlen(name)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(tmp->name_var)) == 0)
		{
			printf("tmp: %s\n", tmp->arg_var);
			free(tmp->arg_var);
			tmp->arg_var = ft_strdup(arg);
			break ;
		}
		tmp = tmp->next;
	}
}

void	add_elem(t_env **list, char *elem_name, char *elem_arg)
{
	t_env	*it;

	it = (*list);
	if (*list == NULL)
		(*list) = create_elem(elem_name, elem_arg);
	else
	{
		while (it->next != NULL)
			it = it->next;
		it->next = create_elem(elem_name, elem_arg);
	}
}

void	add_elem_ord(t_env **list, char *elem_name, char *elem_arg)
{
	t_env	*it;
	t_env	*save;
	int		i;

	i = 0;
	it = (*list);
	if (*list == NULL)
		(*list) = create_elem(elem_name, elem_arg);
	else
	{
		i = add_elem_ord_norme(&it, elem_name);
		if (i == 0)
		{
			save = it->next;
			it->next = create_elem(elem_name, elem_arg);
			it->next->next = save;
		}
		else
		{
			free(it->arg_var);
			it->arg_var = ft_strdup(elem_arg);
		}
	}
}
