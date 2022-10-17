/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:54:17 by anovelli          #+#    #+#             */
/*   Updated: 2022/10/12 14:57:58 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_parser.h"

extern	void	rl_replace_line(const char *text, int clear_undo);

void	quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

/* è un problema per la Giorgia del futuro 42*/
void	received(int sig)
{
	(void)sig;
	ft_putchar_fd((char)127, 1);
	ft_putchar_fd((char)127, 1);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
