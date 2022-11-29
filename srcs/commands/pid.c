/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <alice@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:37:54 by alice             #+#    #+#             */
/*   Updated: 2022/11/29 21:48:32 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_strjoin_3(const char *s1, char *s2, const char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(s2);
	free(tmp);
	return (ret);
}

char	*get_shlvl(t_mini *mini)
{
	t_env	*tmp;
	char	*ret;
	int		i;

	tmp = ft_search_var(mini->env, "SHLVL");
	if (tmp == NULL)
		return (NULL);
	i = ft_atoi(tmp->arg_var);
	ret = ft_itoa(i - 1);
	return (ret);
}

void	my_child_get_pid(t_mini *mini, int *fd)
{
	char		*cmd;
	char		*shlvl;
	const char	*s1;

	shlvl = get_shlvl(mini);
	s1 = "ps | grep -w ./minishell | head -n ";
	cmd = ft_strjoin_3(s1, shlvl, " | tail -n 1 | cut -c 1-6");
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	process_input(mini, cmd);
	close(fd[1]);
}

void	my_pid(t_mini *mini)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	buf[6];

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		my_child_get_pid(mini, fd);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fd[1]);
		dup2(mini->save_out, STDOUT_FILENO);
		read(fd[0], buf, 5);
		mini->pid = get_strip_str(buf, 0, 5, 0);
		close(fd[0]);
	}
}
