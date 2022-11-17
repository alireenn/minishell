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
int	wild_cats(char *entry, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

char 	**what_team(char *filename, char *to_find, char *com, t_mini *mini)
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
		if (wild_cats(entry->d_name, split) == 1)
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
	return(ret);
}

char	*ft_pwd_ft(void)
{
	char	*ret;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ret = strdup(pwd);
	return (ret);
}

// int main (int ac, char **av)
// {
// 	char	*dir;
// 	char	**mat;
// 	(void)ac;

// 	dir = ft_pwd_ft();
// 	mat = what_team(dir, av[1]);
// 	int	i = 0;
// 	while (mat[i] != NULL)
// 	{
// 		printf("%d -> %s\n", i, mat[i]);
// 		i++;
// 	}
// 	free(dir);
// }