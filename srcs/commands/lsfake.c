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
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
int	wild_cats(char *entry, char *to_find, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*entry && split[j])
	{
		if (ft_strnstr(entry, split[j], ft_strlen(entry)) == entry)
			j++;
		entry++;
	}
	if (split[j] == NULL)
		return (1);
	return (0);
}

void	what_team(char *filename, char *to_find)
{
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	// char			*ret;
	// char			*tmp;
	char			**split;

	i = 0;
	split = ft_split(to_find, "*", &i);
	dir = opendir(filename);
	// ret = NULL;
	i = 0;
	if (dir == NULL)
	{
		printf("minishell: %s: Permission denied\n", filename);
		exit(126);
	}
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (wild_cats(entry->d_name, to_find, split) == 1)
		{
			// tmp = ft_strdup(ret);
			// if (tmp == NULL)
			// {
			// 	tmp = malloc(1);
			// 	tmp[0] = '\0';
			// }
			// if (ret != NULL)
			// 	free(ret);
			// ret = ft_strjoin(tmp, entry->d_name);
			// free(tmp);
			printf("%s\n", entry->d_name);
			i++;
		}
	}
	if (i == 0)
		printf("%s\n", to_find);
	// printf("%s\n", ret);
	free(split);
	closedir(dir);
}

char	*ft_pwd_ft(void)
{
	char	*ret;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ret = strdup(pwd);
	return (ret);
}

int main (int ac, char **av)
{
	char	*dir;
	(void)ac;

	dir = ft_pwd_ft();
	what_team(dir, av[1]);
	free(dir);
}