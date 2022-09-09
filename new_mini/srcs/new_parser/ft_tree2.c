/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:00:28 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/17 17:42:27 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

void	print_tree_rec(t_tree a)
{
	if (a == NULL)
		printf("()");
	else
	{
		printf("( %d ", a->info);
		print_tree_rec(a->left);
		printf(" ");
		print_tree_rec(a->right);
		printf(" )");
	}
}

void	print_tree(t_tree *a)
{
	print_tree_rec(*a);
	printf("\n");
}

int	get_tree_size(t_tree a)
{
	if (a == NULL)
		return (0);
	else
		return (1 + get_tree_size(a->left) + get_tree_size(a->right));
}

// get_tree_depth albero
int	get_tree_depth(t_tree a)
{
	int	ps;
	int	pd;

	if (a == NULL)
		return (-1);
	else
	{
		ps = get_tree_depth(a->left);
		pd = get_tree_depth(a->right);
		if (ps >= pd)
			return (ps + 1);
		else
			return (pd + 1);
	}
}

void	free_tree(t_tree *a)
{
	if ((*a) != NULL)
	{
		free_tree(&((*a)->left));
		free_tree(&((*a)->right));
		free(*a);
		(*a) = NULL;
	}
}
