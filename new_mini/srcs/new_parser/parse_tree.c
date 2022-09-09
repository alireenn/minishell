/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 09:50:14 by anovelli          #+#    #+#             */
/*   Updated: 2022/09/09 17:31:04 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

char	*ft_strdup_from_to(char *input, int start, int end)
{
	int		i;
	int		j;
	char	*ret;

	i = start;
	ret = malloc(sizeof(char *) * (end - start + 1));
	j = 0;
	while (j < end - start + 1)
	{
		ret[j] = input[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

int	search_closing(char *input, int c)
{
	int	i;
	int	open;

	open = 1;
	i = c + 1;
	if (c == -1)
		return (-1);
	while (open > 0 && input[i] != 0)
	{
		if (input[i] == '(')
			open++;
		if (input[i] == ')')
			open--;
		i++;
	}
	return (i);
}

t_tree	get_next_tree(char *input, int *ind, int *cmd)
{
	t_tree	ret;
	int		i;
	int		j;

	while (input[*ind] == '>' || input[*ind] == '<')
		(*ind)++;
	i = *ind;
	if (input[i] == '(')
	{
		j = search_closing(input, i);
		// ret = make_tree(ft_strdup_from_to(input, i + 1, j - 2), cmd);
		*ind = j;
	}
	ret = nodoalb_alloc(*cmd);
	(*cmd)++;
	return (ret);
}

t_tree	make_tree(char *input, int *cmd)
{
	int		i;
	int		j;
	t_tree	ret;
	t_tree	sx;

	i = 0;
	//printf("len: %d\n", strlen(input));
	ret = get_next_tree(input, &i, cmd);
	while (input[i] != '\0')
	{
		sx = ret;
		while (input[i] == '>' || input[i] == '<')
			i++;
		if (input[i] == '&')
			ret = nodoalb_alloc(-1);
		if (input[i] == '|')
			ret = nodoalb_alloc(-2);
		if (input[i] == 'p')
			ret = nodoalb_alloc(-3);
		ret->left = sx;
		i++;
		ret->right = get_next_tree(input, &i, cmd);
	}
	return (ret);
}

char	*parse_tree(char *input)
{
	int		i;
	int		j;
	int		cmd;
	char	*ret;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (special_issep(input[i], "()<>"))
			j++;
		if (special_issep(input[i], "&|")
			&& input[i + 1] != '\0' && input[i + 1] == input[i])
		{
			i++;
			j++;
		}
		else if (input[i] == '|' && input[i + 1] != '\0' && input[i + 1] != '&')
			j++;
		else if (special_issep(input[i], "&|") && input[i + 1] != '\0')
		{
			printf("Parse Error\n");
			exit(1);
		}
		i++;
	}
	ret = (char *) malloc (sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (special_issep(input[i], "()<>"))
		{
			ret[j] = input[i];
			j++;
		}
		if (special_issep(input[i], "&|")
			&& input[i + 1] != '\0' && input[i + 1] == input[i])
		{
			ret[j] = input[i];
			i++;
			j++;
		}
		else if (input[i] == '|' && input[i + 1] != '\0' && input[i + 1] != '&')
		{
			ret[j] = 'p';
			i++;
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	check_parse(char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i] != '\0')
	{
		if (parsed[i] == '>' && parsed[i + 1] == '(')
			{
				printf("minishell: parse error near `)'\n");
				return (0);
			}
			else if (parsed[i] == '>' && parsed[i + 1] == '<')
			{
				printf("minishell: syntax error near unexpected token `<'\n");
				return (0);
			}
		i++;
	}
	return (1);	
}

int main(int argc, char **argv)
{
	char 		*parsed;
	t_tree		ret;
	// t_command	**cmds;
	char		**splitted;
	int			cmd;

	if (argc != 2)
		return (0);
	parsed = parse_tree(argv[1]);
	printf("parsed = %s\n", parsed);
	if (!check_parse(parsed))
		return (1);
	cmd = 0;
	ret = make_tree(parsed, &cmd);
	print_tree(&ret);
	splitted = split_parser(argv[1], cmd);
	// cmds = alloc_cmds(cmd);
	free(parsed);
}