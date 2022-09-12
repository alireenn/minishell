/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 23:26:16 by anovelli          #+#    #+#             */
/*   Updated: 2022/01/13 00:41:50 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(len, sizeof(char));
	while (s1[j] != '\0')
	{
		str[i] = (char)s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = (char)s2[j];
		i++;
		j++;
	}
	return (str);
}
