/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:46:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/10 13:00:03 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_tree	null_tree(void)
{
	return (NULL);
}

int	radix(t_tree a)
{
	return (a->info);
}

int	is_null(t_tree a)
{
	return (a == NULL);
}

t_node_tree	*nodoalb_alloc(int e)
{
	t_node_tree	*r;

	r = (t_node_tree *) malloc (sizeof(t_node_tree));
	r->info = e;
	r->right = NULL;
	r->left = NULL;
	return (r);
}

t_tree	create_bin_tree(int infoRadice, t_tree sx, t_tree dx)
{
	t_tree	a;

	a = (t_tree) malloc(sizeof(t_node_tree));
	a->info = infoRadice;
	a->left = sx;
	a->right = dx;
	return (a);
}
