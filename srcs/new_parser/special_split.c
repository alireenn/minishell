/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:01:06 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/22 18:55:28 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

int	is_sep(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	special_strcount(char *s, char *cs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (is_sep(s[i], cs) == 0)
		{
			count++;
			while (s[i] != '\0')
			{
				if (is_sep(s[i], cs) && s[i + 1] != '\0' && s[i + 1] == s[i])
				{
					i++;
					if (s[i + 1] != '\0' && is_sep(s[i + 1], cs) == 0)
						break ;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

int	special_strlen(char *s, char *cs)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (is_sep(s[i], cs) == 0)
		{
			while (s[i] != '\0')
			{
				if (is_sep(s[i], cs) && s[i + 1] != '\0' && s[i + 1] == s[i])
				{
					i++;
					if (s[i + 1] != '\0' && is_sep(s[i + 1], cs) == 0)
						break ;
					len++;
				}
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

int	special_putstr(char *str, char *charset, char *matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (is_sep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{
				if (is_sep(str[i], charset) == 1
					&& str[i + 1] != '\0' && str[i + 1] == str[i])
				{
					i++;
					matrix[j] = str[i];
					j++;
					if (str[i + 1] != '\0'
						&& is_sep(str[i + 1], charset) == 0)
					{
						i--;
						j--;
						break ;
					}
				}
				matrix[j] = str[i];
				j++;
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

char	**special_split(char *str, char *charset, int *c)
{
	int		count;
	char	**matrix;
	int		row;
	int		len;
	int		offset;

	offset = 0;
	count = special_strcount(str, charset);
	(*c) = count;
	matrix = (char **) malloc (sizeof(char *) * count + 1);
	matrix[count] = 0;
	row = 0;
	while (row < count)
	{
		len = special_strlen(str, charset);
		matrix[row] = (char *) malloc (sizeof(char) * len + 1);
		offset = special_putstr(str, charset, matrix[row]);
		str += offset;
		row++;
	}
	return (matrix);
}
