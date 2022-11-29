/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/29 16:44:24 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

int	free_mini(t_mini *mini)
{
	int	ret;

	ret = mini->last;
	if (mini->env != NULL)
		free_env(mini->env);
	if (mini->secret != NULL)
		free_env(mini->secret);
	if (mini->pwd != NULL)
		free(mini->pwd);
	close(mini->save_in);
	close(mini->save_out);
	free(mini);
	return (ret);
}

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
	int		ret;
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
		ret = WEXITSTATUS(status);
	}
}

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handle);
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_mini	*mini;
	char	*prompt;

	if (argc > 1)
		return (printf("Minishell: %s: No such file or directory\n", argv[1]));
	ft_sig();
	mini = init_mini(envp);
	my_pid(mini);
	prompt = our_prompt(mini->res, mini);
	while (prompt != NULL)
	{
		while (incomplete_cmd(prompt) == 0)
			prompt = get_other_input(prompt);
		process_input_aux(mini, prompt);
		free(prompt);
		if (mini->exit == 1)
			break ;
		prompt = our_prompt(mini->res, mini);
	}
	ret = free_mini(mini);
	return (ret);
}
