/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:30:02 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/05 13:32:29 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	wild_cats(char *entry, char **split, char *to_find)
{
	int	j;
	int	len;

	len = 0;
	if (split[len] == NULL && entry[0] != '.')
		return (1);
	else if (split[len] == NULL)
		return (0);
	j = 0;
	if (troyella(split, to_find, entry) == 0)
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

void	what_time_is_it(char **ret, char *to_find)
{
	char	**tmp;
	int		i;

	i = 0;
	if (ft_strlen(*ret) == 0)
	{
		free(*ret);
		*ret = ft_strdup(to_find);
	}
	else
	{
		tmp = ft_split(*ret, " ", &i);
		order_mat(tmp, i);
		free(*ret);
		*ret = join_mat(tmp, 1);
	}
}

char	*playmaker(char *to_find, char **split, DIR *dir)
{
	char			*ret;
	char			*temp;
	struct dirent	*entry;

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
	what_time_is_it(&ret, to_find);
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
