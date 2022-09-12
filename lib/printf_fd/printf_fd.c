/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:45:57 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:37:52 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_fd(int fd, const char *str, ...)
{
	int		i;
	va_list	args;
	int		print_length;

	i = 0;
	print_length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_length += ft_get_arg(fd, &args, (char *)str, &i);
		}
		else
			print_length += ft_printchar(fd, str[i]);
		i++;
	}
	va_end(args);
	return (print_length);
}
