/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:21:10 by anovelli          #+#    #+#             */
/*   Updated: 2022/01/15 16:44:32 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	checkchar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	while (checkchar(s1[i], set))
		i++;
	if (s1[i] == 0)
	{
		str = malloc(sizeof(char));
		str[0] = 0;
		return (str);
	}
	while (s1[j] != 0)
		j++;
	j--;
	while (checkchar(s1[j], set))
		j--;
	str = ft_calloc(j - i + 2, sizeof(char));
	ft_memcpy(str, &s1[i], j - i + 1);
	return (str);
}
