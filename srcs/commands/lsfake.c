/* ************************************************************************** */
/*		                                                                      */
/*                                                        :::      ::::::::   */
/*   lsfake.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:57:25 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/10 14:52:44 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	remove_quotes_mat(char **matrix)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!matrix || !matrix[i])
		return ;
	while (matrix[i])
	{
		tmp = remove_quotes_str(matrix[i]);
		free(matrix[i]);
		matrix[i] = tmp;
		i++;
	}
}

char	*join_mat(char **matrix, int flag)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 1;
	ret = ft_strdup(matrix[0]);
	free(matrix[0]);
	while (matrix[i])
	{
		tmp = ret;
		ret = ft_join_char(tmp, matrix[i], ' ');
		if (flag == 1)
			free(matrix[i]);
		i++;
		if (tmp != NULL)
			free(tmp);
	}
	if (flag == 1)
		free(matrix);
	return (ret);
}

void	order_mat(char **matrix, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = size - 1;
		while (j >= i + 1)
		{
			if (equal_strings(matrix[j - 1], matrix[j]) > 0)
			{
				tmp = matrix[j];
				matrix[j] = matrix[j - 1];
				matrix[j - 1] = tmp;
			}
			j--;
		}
		i++;
	}
}

int	troyella(char **split, char *to_find, char *entry)
{
	int	len;

	len = 0;
	while (split[len])
		len++;
	if (to_find[0] != '*' && ft_strncmp(split[0], entry,
			ft_strlen(split[0])) != 0)
		return (0);
	if (ft_strlen(entry) - ft_strlen(split[len - 1]) > 0)
		if (to_find[ft_strlen(to_find) - 1] != '*' && ft_strncmp(split[len - 1],
				&entry[ft_strlen(entry) - ft_strlen(split[len - 1])],
				ft_strlen(split[len - 1])) != 0)
			return (0);
	return (1);
}

char	*ft_pwd_ft(void)
{
	char	*ret;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ret = strdup(pwd);
	return (ret);
}
