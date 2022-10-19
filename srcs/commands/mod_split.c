/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:52:53 by gcucino           #+#    #+#             */
/*   Updated: 2022/10/19 12:58:19 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/new_parser.h"

int	mod_helper(char *str, int i, char *avoid, int open)
{
	if (is_sep(str[i], avoid) == 1 && open == 0)
		open++;
	else if (is_sep(str[i], avoid) == 1)
		open--;
	return (open);
}

int	mod_strcount(char *str, char *charset, char *avoid)
{
	int	i;
	int	count;
	int	open;

	i = 0;
	count = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 0)
		{
			count++;
			while (str[i] != '\0')
			{
				open = mod_helper(str, i, avoid, open);
				if (is_sep(str[i], charset) == 1 && open == 0)
					break ;
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

int culo()
{
	
}

int	mod_putstr(char *str, char *charset, char *matrix, char *avoid)
{
	int	i;
	int	j;
	int	open;

	i = 0;
	j = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{	
				if (is_sep(str[i], charset) == 1 && open == 0)
					break ;
				if (is_sep(str[i], avoid) == 1 && open == 0)
					open++;
				else if (is_sep(str[i], avoid) == 1)
					open--;
				else
					matrix[j++] = str[i];
				i++;
			}
			matrix[j] = '\0';
			return (i);
		}
		else
			i++;
	}
	return (0);
}

int	mod_strlen(char *str, char *charset, char *avoid)
{
	int	i;
	int	len;
	int	open;

	i = 0;
	len = 0;
	open = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{
				open = mod_helper(str, i, avoid, open);
				if (is_sep(str[i], charset) == 1 && open == 0)
					break ;
				i++;
				len++;
			}
			return (len);
		}
		else
			i++;
	}
	return (0);
}

char	**mod_split(char *str, char *charset, char *avoid)
{
	int		count;
	char	**matrix;
	int		row;
	int		len;
	int		offset;

	offset = 0;
	count = mod_strcount(str, charset, avoid);
	matrix = (char **) malloc (sizeof(char *) * count + 1);
	matrix[count] = 0;
	row = 0;
	while (row < count)
	{
		len = mod_strlen(str, charset, avoid);
		matrix[row] = (char *) malloc (sizeof(char) * len + 1);
		offset = mod_putstr(str, charset, matrix[row], avoid);
		str += offset;
		row++;
	}
	return (matrix);
}