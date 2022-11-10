/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:42:16 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/10 14:42:39 by anovelli         ###   ########.fr       */
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
