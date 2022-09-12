/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:27:42 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:41:39 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printp(int fd, unsigned long long n, int flag)
{
	if (n < 10)
		return (ft_printchar(fd, n + '0'));
	else if (n < 16)
		return (ft_printchar(fd, n - 10 + (flag * 32) + 'A'));
	else
		return (ft_printp(fd, n / 16, flag) + ft_printp(fd, n % 16, flag));
}

int	ft_print_ptr(int fd, void *ptr)
{
	int					ret;
	unsigned long long	n;

	ret = 0;
	n = (unsigned long long) ptr;
	ret += write(fd, "0x", 2);
	if (ptr == 0)
		ret += write(fd, "0", 1);
	else
		ret += ft_printp(fd, n, 1);
	return (ret);
}
