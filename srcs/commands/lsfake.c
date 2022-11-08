/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsfake.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:57:25 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:25 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../../lib/libft/libft.h"

void	wild_cats(char *entry, char *to_find)
{
    int 	i;
	int		j;
	char	**split;
	char	*cpy;
    
	i = 0;
	j = 0;
	cpy = ft_strdup(entry);
	split = ft_split(to_find, "*", &i);
	// if (split[j])
	while (*entry && split[j])
	{
		if (ft_strnstr(entry, split[j], ft_strlen(entry)) == entry)
			j++;
		entry++;
	}
	if (split[j] == NULL)
		printf("%s\n", cpy);
	else
	{
		printf("%s\n", to_find);
		return ;
	}
}

void	ls_fake(char *filename, char *to_find)
{
    DIR 			*dir;
    struct dirent	*entry;
	int				i;

    dir = opendir(filename);
    if (dir == NULL)
    {
		printf("minishell: %s: Permission denied\n", filename);
		exit(126);
    }
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break;
		// printf("%s\n", entry->d_name);
    	wild_cats(entry->d_name, to_find);
	}
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
	(void)ac;
	ls_fake(ft_pwd_ft(), av[1]);
}