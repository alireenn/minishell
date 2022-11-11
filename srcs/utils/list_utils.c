/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:42:16 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/11 17:58:27 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_elem_ord_help(t_env *it, char *elem_name)
{
	if (ft_strncmp(it->name_var, elem_name,
			ft_strlen(elem_name)) < 0
		&& ft_strncmp(it->next->name_var, elem_name,
			ft_strlen(elem_name)) > 0)
		return (1);
	return (0);
}

int	add_elem_ord_norme(t_env **it, char *elem_name)
{
	while ((*it)->next != NULL)
	{
		if (ft_strlen((*it)->name_var) == ft_strlen(elem_name)
			&& ft_strncmp((*it)->name_var, elem_name,
				ft_strlen(elem_name)) == 0)
			return (1);
		else if (add_elem_ord_help(*it, elem_name) == 1)
			return (0);
		*it = (*it)->next;
	}
	return (0);
}
