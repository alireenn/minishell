/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:54:17 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/02 21:55:13 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

extern	void	rl_replace_line(const char *text, int clear_undo);

void	sig_handle(int sig)
{
	int	flag;

	flag = 0;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		if (ft_strlen(rl_line_buffer) == 0)
			flag = 1;
		rl_replace_line("", 0);
		if (flag == 1)
			rl_redisplay();
	}
}

void	ft_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handle);
}
