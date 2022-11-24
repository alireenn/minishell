/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 15:39:24 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/24 19:16:40 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incl/minishell.h"

void	free_mini(t_mini *mini)
{
	if (mini->env != NULL)
		free_env(mini->env);
	if (mini->secret != NULL)
		free_env(mini->secret);
	if (mini->pwd != NULL)
		free(mini->pwd);
	close(mini->save_in);
	close(mini->save_out);
	free(mini);
}

char	*our_prompt(int res, t_mini *mini)
{
	char	*tmp;
	char	*ret;

	if (res == 1)
	{
		tmp = ft_strjoin("✅ ", "Minishell ➡ ");
		mini->last = 0;
	}
	else
		tmp = ft_strjoin("❌ ", "Minishell ➡ ");
	ret = readline(tmp);
	free(tmp);
	return (ret);
}

void	process_input_aux(t_mini *mini, char *input)
{
	if (input[0] == '\0')
		return ;
	add_history(input);
	process_input(mini, input);
}
	// int i = 0;
	// while (i < mini->cmd)
	// {
	// 	printf("%s\n", splitted[i]);
	// 	i++;
	// }

	// printf("parsed = %s, %d\n", parsed, mini->cmd);

int	incomplete_cmd(char *input)
{
	int	i;

	i = (int)ft_strlen(input) - 1;
	while (input[i] == ' ')
		i--;
	if (input[i] == '|' || input[i] == '&')
		return (0);
	else
		return (1);
}

char	*get_other_input(char *input)
{
	char	*tmp;
	char	*ret;

	tmp = readline("> ");
	ret = ft_strjoin(input, tmp);
	free(tmp);
	free(input);
	return (ret);
}

void	process_input(t_mini *mini, char *input)
{
	char	*parsed;
	char	**splitted;

	parsed = parse_tree(input);
	if (!check_parse(parsed))
		return ;
	mini->cmd = 0;
	mini->tree = make_tree(parsed, &(mini->cmd));
	splitted = split_parser(input, mini->cmd);
	mini->commands = alloc_cmds(mini->cmd);
	get_redirs(splitted, mini->commands, mini->cmd, mini);
	expand(splitted, mini);
	get_cmds(mini->commands, mini->cmd, splitted);
	// print_cmds(mini->commands, mini->cmd);
	mini->res = execute(mini->tree, mini->commands, mini);
	// print_cmds(mini->commands, mini->cmd);
	//mini->exit = 1;
	free_cmds(mini->commands, mini->cmd);
	free_tree(&(mini->tree));
	free_matrix(splitted, mini->cmd);
	free(parsed);
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
	//char *ret = ft_strdup(tmp->arg_var);
	return (ret);
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		process_input(mini, ft_strjoin_3("ps | grep -w ./minishell | head -n ", get_shlvl(mini), " | tail -n 1 | cut -d' ' -f1"));
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		dup2(mini->save_out, STDOUT_FILENO);
		printf("%zd\n", read(fd[0], buf, 5));
		buf[5] = '\0';
		printf("%s\n", buf);
		close(fd[0]);
		ret = WEXITSTATUS(status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		ret;
	t_mini	*mini;
	char	*prompt;

	if (argc > 1)
		return (printf("Minishell: %s: No such file or directory\n", argv[1]));
	(void)argc;
	(void)argv;
	signal(SIGINT, received);
	signal(SIGQUIT, quit);
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
	ret = mini->last;
	free_mini(mini);
	return (ret);
}
