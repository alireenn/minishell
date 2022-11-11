/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:25:42 by gcucino           #+#    #+#             */
/*   Updated: 2022/11/10 14:35:52 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	change_fd(t_command *cmd)
{
	if (cmd->red[1] != 0)
		dup2(cmd->fd_red[1], STDOUT_FILENO);
	if (cmd->red[0] != 0)
		dup2(cmd->fd_red[0], STDIN_FILENO);
}

t_env	*copy_env(t_mini *mini, int *n)
{
	int		i;
	t_env	*it;
	t_env	*ret;
	t_env	*new;
	t_env	*tmp;

	it = mini->env;
	i = 1;
	tmp = create_elem(it->name_var, it->arg_var);
	ret = tmp;
	it = it->next;
	while (it != NULL)
	{
		new = create_elem(it->name_var, it->arg_var);
		tmp->next = new;
		tmp = new;
		it = it->next;
		i++;
	}
	(*n) = i;
	return (ret);
}

t_env	*ft_search_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strlen(name) == ft_strlen(tmp->name_var)
			&& ft_strncmp(tmp->name_var, name, ft_strlen(name)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	split_at(char *input, t_env *env, char c)
{
	int		i;
	int		j;

	i = 0;
	while (input[i] != '\0' && input[i] != c)
		i++;
	j = 0;
	env->name_var = malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		env->name_var[j] = input[j];
		j++;
	}
	env->name_var[j] = '\0';
	if (input[i] == '\0')
		env->arg_var = NULL;
	else
		env->arg_var = ft_strdup(&input[i + 1]);
	env->next = NULL;
}

void	back_to_standard(t_command *cmd, t_mini *mini)
{
	if (cmd->red[1] != 0)
	{
		close(cmd->fd_red[1]);
		dup2(mini->save_out, STDOUT_FILENO);
	}
	if (cmd->red[0] != 0)
	{
		close(cmd->fd_red[0]);
		dup2(mini->save_in, STDIN_FILENO);
	}
}
