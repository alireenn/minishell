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

int wild_cats(char *entry)
{
    int i;

    i = 0
}

void    ls_fake(char *filename)
{
    DIR *dir;
    struct dirent *entry;

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
        if (wild_cats(entry->d_name) == 1)
		    //printf("%s\n", entry->d_name); 
	}
	//tvb <3
    closedir(dir);
}

char	*ft_pwd(void)
{
	char	*ret;
	char	pwd[PATH_MAX];

	getcwd(pwd, PATH_MAX);
	ret = strdup(pwd);
	return (ret);
}

int main (void)
{
	ls_fake(ft_pwd());
}