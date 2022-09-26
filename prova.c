/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prova.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:45:06 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/26 13:10:23 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void	print_pid(int pid)
{
	printf("%d\n", pid);
}

void	handler(int signo, siginfo_t *info, void *context)
{
	int	i;

	context = (ucontext_t *)context;
	i = info->si_pid;
}

int	main(void)
{
	pid_t				pd;
	int					ret;
	struct sigaction	act1;
	// int					fd[2];

	act1.sa_flags = SA_SIGINFO;
	act1.sa_sigaction = &handler;
	// ret = pipe(fd);
	if (sigaction(SIGUSR1, &act1, NULL) == -1)
		exit(1);
	pd = fork();
	if (pd == 0)
	{
		printf("[Figlio] pd = %d, pid = %d\n", pd, getpid());
		exit(0);
	}
	printf("[Padre] pd = %d, pid = %d\n", pd, getpid());
	kill(pd, SIGUSR1);
	ret = wait(NULL);
}
