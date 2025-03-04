/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opopov <opopov@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:21:47 by opopov            #+#    #+#             */
/*   Updated: 2025/03/04 14:52:09 by opopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void	string_send(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(42);
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(42);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3 || ft_strlen(argv[2]) == 0 || ft_atoi(argv[1]) <= 0)
		return (ft_putstr_fd("Error: invalid input.\n", 2));
	ft_putstr_fd("Sent: ", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putchar_fd('\n', 1);
	string_send(ft_atoi(argv[1]), argv[2]);
	return (0);
}
