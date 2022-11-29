/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:52:53 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/29 17:20:57 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	mod_putstr(char *str, char *charset, char *matrix, char *avoid) //fai array e b_zero
{
	int	a[3]; // 0=i, 1=j, 2=open

	ft_bzero(a, 0);
	while (str[a[0]] != '\0')
	{
		if (is_sep(str[a[0]], charset) == 0)
		{
			while (str[a[0]] != '\0' && !(is_sep(str[a[0]], charset) == 1 && !a[2]))
			{
				if (is_sep(str[a[0]], avoid) == 1)
					a[2] = !a[2];
				else
					matrix[a[1]++] = str[a[0]];
				a[0]++;
			}
			matrix[a[1]] = '\0';
			return (a[0]);
		}
		else
			a[0]++;
	}
	return (0);
}
