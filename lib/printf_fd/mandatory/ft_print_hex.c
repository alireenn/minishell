/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:35:32 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:40:30 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_ex(int fd, unsigned int n, int flag)
{
	int		ret;

	ret = ft_printp(fd, n, flag);
	return (ret);
}
