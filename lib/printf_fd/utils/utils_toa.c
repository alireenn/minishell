/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_toa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:08:14 by gcucino           #+#    #+#             */
/*   Updated: 2022/02/04 19:18:53 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	ft_convert_ex(int n, int nc)
{
	if (n < 10)
		return (n + 48);
	else
		return (n - 10 + 65 + (32 * nc));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcpy(char *str)
{
	int		i;
	char	*ret;

	if (str == NULL)
		return (NULL);
	i = 0;
	ret = (char *) malloc (sizeof(char) * (int)ft_strlen(str) + 1);
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
