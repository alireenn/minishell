/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:04:38 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:42:25 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr(int fd, unsigned int n)
{
	if (n < 10)
		return (ft_printchar(fd, n + '0'));
	else
		return (ft_putnbr(fd, n / 10) + ft_putnbr(fd, n % 10));
}

int	ft_printnbr(int fd, int n)
{
	unsigned int	nb;
	int				ret;

	ret = 0;
	if (n < 0)
	{
		ret += ft_printchar(fd, '-');
		nb = -n;
	}
	else
		nb = n;
	ret += ft_putnbr(fd, nb);
	return (ret);
}
