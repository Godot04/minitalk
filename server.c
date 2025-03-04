/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:21:53 by opopov            #+#    #+#             */
/*   Updated: 2025/03/04 15:10:28 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	server_action(int signum, siginfo_t *info, void *tmp)
{
	static int				i = 0;
	static __pid_t			usr_pid = 0;
	static unsigned char	ch = 0;

	(void)tmp;
	if (!usr_pid)
		usr_pid = info->si_pid;
	if (usr_pid != info->si_pid)
		exit (ft_putstr_fd
			("Error: signals from 2 users at the same time.\n", 2));
	if (signum == SIGUSR2)
		ch |= 1;
	if (++i == 8)
	{
		i = 0;
		if (ch == '\0')
		{
			usr_pid = 0;
			return ;
		}
		ft_putchar_fd(ch, 1);
		ch = 0;
	}
	else
		ch <<= 1;
}

int	main(void)
{
	struct sigaction	sa;
	int					a;
	int					b;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = server_action;
	sa.sa_flags = SA_SIGINFO;
	a = sigaction(SIGUSR1, &sa, NULL);
	b = sigaction(SIGUSR2, &sa, NULL);
	if (a == -1 || b == -1)
	{
		ft_putstr_fd("Error: signal translating failed.\n", 2);
		exit (1);
	}
	while (1)
		pause();
	return (0);
}
