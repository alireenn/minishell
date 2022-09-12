/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:00:14 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:43:22 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printchar(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}
