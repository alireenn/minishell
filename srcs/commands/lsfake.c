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

typedef struct wild{
	char	*name;
	struct wild	*next;
}	wildcard;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((s11[i] == s22[i] && s11[i] != '\0') && ((i + 1) < n))
	{
		i++;
	}
	return (s11[i] - s22[i]);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

void	wild_cats(char *entry, char *to_find)
{
    int 	i;
	int		ast;
	char	*replace;

    i = 0;
	ast = 0;
	//caso in cui sia solo un *
	while (to_find[i])
	{
		if (to_find[i] == '*')
			ast++;
		i++;
	}
	i = 0;
	while (to_find[i] != '*')
		i++;
	if (ast == 1)
	{
		if (ft_strncmp(entry, to_find, i + 1) == 0 && ft_strncmp(entry, to_find + (i + 1), ft_strlen(to_find) == 0))
			printf("%s\n", entry); 
	}
}

void	ls_fake(char *filename, char *to_find)
{
    DIR 			*dir;
    struct dirent	*entry;
	int				i;
	wildcard		*wild;

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
		printf("%s\n", entry->d_name);
		// wild->name = malloc(sizeof(char *) * ft_strlen(entry->d_name));
		// wild->name = entry->d_name;
		// wild = wild->next;
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
	// printf("%s", av[1]);
	ls_fake(ft_pwd_ft(), av[1]);
}