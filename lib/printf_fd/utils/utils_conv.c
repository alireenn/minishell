/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:01:44 by gcucino           #+#    #+#             */
/*   Updated: 2022/02/05 14:14:26 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	skip_spaces(const char *str, int *i)
{
	while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v'
		|| str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	ret;
	int	sign;

	i = 0;
	ret = 0;
	sign = 1;
	skip_spaces(str, &i);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret += str[i] - 48;
		if (str[i + 1] >= '0' && str[i + 1] <= '9')
			ret *= 10;
		i++;
	}
	return (ret * sign);
}

unsigned int	ft_atou(const char *str)
{
	int				i;
	unsigned int	ret;

	i = 0;
	ret = 0;
	while (ft_char_in_set(str[i], "1234567890abcdefABCDEF"))
	{
		if (ft_char_in_set(str[i], "1234567890"))
			ret += str[i] - 48;
		else if (ft_char_in_set(str[i], "abcdef"))
			ret += str[i] - 97;
		else
			ret += str[i] - 65;
		if (ft_char_in_set(str[i + 1], "1234567890abcdefABCDEF"))
			ret *= 16;
		i++;
	}
	return (ret);
}
