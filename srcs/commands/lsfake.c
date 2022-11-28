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
// #include "../../lib/libft/libft.h"
// # include <unistd.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include <string.h>
// # include <dirent.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <limits.h>
// # include <sys/types.h>
// # include <sys/wait.h>
int	wild_cats(char *entry, char **split, char *to_find)
{
	int	j;
	int	len;

	len = 0;
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

char	**what_team(char *filename, char *to_find, char *com, t_mini *mini)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	char			**ret;
	char			**split;

	i = 0;
	if (ft_strchr(to_find, ' ') != 0)
	{
		while (*(to_find) != ' ')
			to_find++;
	}
	split = ft_split(to_find, "*", &i);
	ret = NULL;
	dir = opendir(filename);
	if (dir == NULL)
	{
		printf("minishell: %s: Permission denied\n", filename);
		exit(126);
	}
	i = 1;
	ret = ft_calloc(sizeof(char *), 100);
	ret[0] = ft_strdup(com);
	while (i < 100)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (wild_cats(entry->d_name, split, to_find) == 1)
		{
			ret[i] = ft_strdup(entry->d_name);
			i++;
		}
	}
	if (i == 1)
	{
		mini->last = 1;
		return (NULL);
	}
	free(split);
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
