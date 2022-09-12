/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 13:13:05 by gcucino           #+#    #+#             */
/*   Updated: 2022/06/16 14:00:13 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_issep(char c, char *str)
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

int	ft_strcount(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_issep(str[i], charset) == 0)
		{
			count++;
			while (str[i] != '\0')
			{
				if (ft_issep(str[i], charset) == 1)
					break ;
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

int	ft_strlen_2(char *str, char *charset)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (ft_issep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{
				if (ft_issep(str[i], charset) == 1)
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

int	ft_putstr(char *str, char *charset, char *matrix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_issep(str[i], charset) == 0)
		{
			while (str[i] != '\0')
			{
				if (ft_issep(str[i], charset) == 1)
					break ;
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

char	**ft_split(char *str, char *charset, int *c)
{
	int		count;
	char	**matrix;
	int		row;
	int		len;
	int		offset;

	offset = 0;
	count = ft_strcount(str, charset);
	(*c) = count;
	matrix = (char **) malloc (sizeof(char *) * count + 1);
	matrix[count] = 0;
	row = 0;
	while (row < count)
	{
		len = ft_strlen_2(str, charset);
		matrix[row] = (char *) malloc (sizeof(char) * len + 1);
		offset = ft_putstr(str, charset, matrix[row]);
		str += offset;
		row++;
	}
	return (matrix);
}
