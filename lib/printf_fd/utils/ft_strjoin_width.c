/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:08:53 by gcucino           #+#    #+#             */
/*   Updated: 2022/09/24 16:08:50 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_set_ret(char *src, int size, int zero)
{
	int	i;

	i = 0;
	while (i < size)
	{
		src[i] = (' ' + (zero * 16));
		i++;
	}
}

char	*ft_strjoin_width(char *s, int width, int minus, int zero)
{
	char	*ret;
	int		s_len;
	int		i;

	i = -1;
	s_len = (int)ft_strlen(s);
	if (width <= s_len)
		return (s);
	ret = (char *) malloc ((width + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_set_ret(ret, width, zero);
	while (++i < s_len)
		ret[i + ((width - s_len) * !minus)] = s[i];
	ret[width] = '\0';
	free(s);
	return (ret);
}

char	*ft_strjoin_width_sign(char *s, int width, int minus, int zero)
{
	char	*ret;
	int		s_len;
	int		i;

	i = 0;
	s_len = (int)ft_strlen(s);
	if (width < s_len)
		return (s);
	ret = (char *) malloc ((width + 2) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_set_ret(ret, width, zero);
	while (++i < s_len)
		ret[i + ((width - s_len) * !minus) + 1] = s[i];
	ret[0] = '-';
	ret[width + 1] = '\0';
	free(s);
	return (ret);
}

char	*_ft_strjoin(char const *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = (char *) malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		ret[i + j] = s2[j];
		j++;
	}
	free(s2);
	ret[i + j] = '\0';
	return (ret);
}
