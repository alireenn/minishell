/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:59:52 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/18 12:18:43 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_get_arg(int fd, va_list *args, char *str, int *i)
{
	int	print_len;

	print_len = 0;
	if (str[*i] == 'c')
		print_len += ft_printchar(fd, va_arg(*args, int));
	else if (str[*i] == 's')
		print_len += ft_printstr(fd, va_arg(*args, char *));
	else if (str[*i] == 'p')
		print_len += ft_print_ptr(fd, va_arg(*args, void *));
	else if (str[*i] == 'd' || str[*i] == 'i')
		print_len += ft_printnbr(fd, va_arg(*args, int));
	else if (str[*i] == 'u')
		print_len += ft_printuns(fd, va_arg(*args, unsigned int));
	else if (str[*i] == 'x' || str[*i] == 'X')
		print_len += ft_print_ex(fd, va_arg(*args, unsigned int),
				str[*i] == 'x');
	else if (str[*i] == '%')
		print_len += ft_printchar(fd, '%');
	return (print_len);
}
