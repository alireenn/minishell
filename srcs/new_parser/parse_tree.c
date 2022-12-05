/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:50:14 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/05 13:36:32 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*parse_tree(char *in)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (in[i] != '\0')
	{
		if (is_sep(in[i], "\"\'"))
			i = search_closing(in, i, in[i], in[i]);
		if (is_sep(in[i], "&|") && in[i + 1] != '\0' && in[i + 1] == in[i])
		{
			i++;
			j++;
		}
		else if ((in[i] == '|' && in[i + 1] != '\0' && in[i + 1] != '&')
			|| (is_sep(in[i], "()<>")))
			j++;
		if (in[i] == '(' && check_syntax(in, i) == 0)
			return (NULL);
		i++;
	}
	ret = (char *) malloc (sizeof(char) * (j + 1));
	parse_tree_helper(in, ret);
	return (ret);
}

t_tree	make_tree(char *input, int *cmd, int pipe)
{
	int		i;
	t_tree	ret;
	t_tree	sx;

	i = 0;
	ret = get_next_tree(input, &i, cmd, pipe);
	while (input[i] != '\0')
	{
		sx = ret;
		while (input[i] == '>' || input[i] == '<')
			i++;
		if (input[i] == '\0')
			return (ret);
		if (input[i] == '&')
			ret = nodoalb_alloc(-1);
		if (input[i] == '|')
			ret = nodoalb_alloc(-2);
		if (input[i] == 'p')
			ret = nodoalb_alloc(-3);
		ret->left = sx;
		i++;
		ret->right = get_next_tree(input, &i, cmd, pipe);
	}
	return (ret);
}

int	search_closing(char *input, int c, char c1, char c2)
{
	int	i;
	int	open;

	open = 1;
	i = c + 1;
	if (c == -1)
		return (-1);
	while (open > 0 && input[i] != 0)
	{
		if (input[i] == c2)
			open--;
		else if (input[i] == c1)
			open++;
		i++;
	}
	return (i);
}

t_tree	get_next_tree(char *input, int *ind, int *cmd, int pipe)
{
	t_tree	ret;
	int		i;
	int		j;

	while (input[*ind] == '>' || input[*ind] == '<')
		(*ind)++;
	i = *ind;
	if (input[i] == '(')
	{
		j = search_closing(input, i, '(', ')');
		*ind = j;
	}
	if (input[i] == 'p' && pipe == 0)
	{
		ret = essential_pipe(input, ind, cmd);
		return (ret);
	}
	ret = nodoalb_alloc(*cmd);
	(*cmd)++;
	return (ret);
}

char	*ft_strdup_from_to(char *input, int start, int end)
{
	int		i;
	int		j;
	char	*ret;

	i = start;
	ret = malloc(sizeof(char) * (end - start + 1));
	j = 0;
	while (j < end - start + 1)
	{
		ret[j] = input[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
