/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:46:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/17 17:42:24 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

t_node_tree	*nodoalb_alloc(int e)
{
	t_node_tree	*r;

	r = (t_node_tree *) malloc (sizeof(t_node_tree));
	r->info = e;
	r->right = NULL;
	r->left = NULL;
	return (r);
}

t_tree	null_tree(void)
{
	return (NULL);
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

int	is_null(t_tree a)
{
	return (a == NULL);
}

int	radix(t_tree a)
{
	return (a->info);
}
