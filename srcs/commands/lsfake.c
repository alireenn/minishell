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

int	wild_cats(char *entry, char **split, char *to_find)
{
	int	j;
	int	len;

	len = 0;
	if (split[len] == NULL && entry[0] != '.')
		return (1);
	else if (split[len] == NULL)
		return (0);
	while (split[len])
		len++;
	j = 0;
	if (to_find[0] != '*' && ft_strncmp(split[0], entry,
			ft_strlen(split[0])) != 0)
		return (0);
	if (ft_strlen(entry) - ft_strlen(split[len - 1]) > 0)
		if (to_find[ft_strlen(to_find) - 1] != '*' && ft_strncmp(split[len - 1],
				&entry[ft_strlen(entry) - ft_strlen(split[len - 1])],
				ft_strlen(split[len - 1])) != 0)
			return (0);
	while (*entry && split[j])
	{
		if (ft_strnstr(entry, split[j], ft_strlen(split[j])) == entry)
			j++;
		entry++;
	}
	if (split[j] == NULL)
		return (1);
	return (0);
}

char	*playmaker(char *to_find, char **split, DIR *dir)
{
	char			*ret;
	char			*temp;
	struct dirent	*entry;
	char			**tmp;
	int				i;

	i = 0;
	ret = ft_strdup("");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (wild_cats(entry->d_name, split, to_find) == 1)
		{
			temp = ret;
			ret = ft_join_char(temp, entry->d_name, ' ');
			free(temp);
		}
		entry = readdir(dir);
	}
	if (ft_strlen(ret) == 0)
	{
		free(ret);
		ret = ft_strdup(to_find);
	}
	else
	{
		tmp = ft_split(ret, " ", &i);
		order_mat(tmp, i);
		free(ret);
		ret = join_mat(tmp, 1);
	}
	return (ret);
}

char	*what_team(char *filename, char *to_find)
{
	DIR				*dir;
	char			*ret;
	char			**split;

	split = mod_split(to_find, "*", "\'\"");
	dir = opendir(filename);
	if (dir == NULL)
	{
		printf_fd(2, "minishell: %s: Permission denied\n", filename);
		exit(126);
	}
	ret = playmaker(to_find, split, dir);
	free_matrix_no_rows(split);
	free(filename);
	closedir(dir);
	return (ret);
}

char	*ft_pwd_ft(void)
{
	char	*ret;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ret = strdup(pwd);
	return (ret);
}
