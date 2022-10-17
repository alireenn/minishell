/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:32 by gcucino           #+#    #+#             */
/*   Updated: 2022/10/13 17:02:26 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

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
		while (it->next != NULL && i == 0)
		{
			if (ft_strlen(it->name_var) == ft_strlen(elem_name)
				&& ft_strncmp(it->name_var, elem_name,
					ft_strlen(elem_name)) == 0)
			{
				i = 1;
				break ;
			}
			else if (ft_strncmp(it->name_var, elem_name,
					ft_strlen(elem_name)) < 0
				&& ft_strncmp(it->next->name_var, elem_name,
					ft_strlen(elem_name)) > 0)
				break ;
			it = it->next;
		}
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

void	change_var(t_env *env, char *name, char *arg)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(tmp->name_var) == ft_strlen(name)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(tmp->name_var)) == 0)
		{
			free(tmp->arg_var);
			tmp->arg_var = ft_strdup(arg);
			break ;
		}
		tmp = tmp->next;
	}
}
