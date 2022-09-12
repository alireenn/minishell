/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:18:13 by anovelli          #+#    #+#             */
/*   Updated: 2022/01/15 12:39:11 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	control(size_t len_dest, size_t len_src, size_t dstsize)
{
	size_t	sum;

	if (dstsize > len_dest)
		sum = len_src + len_dest;
	else
		sum = len_src + dstsize;
	return (sum);
}

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	sum;
	size_t	i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	i = 0;
	sum = control(len_dest, len_src, dstsize);
	if (dstsize > 0 && len_dest <= dstsize)
	{
		while (src[i] && (len_dest + 1) < dstsize)
		{
			dest[len_dest] = src[i];
			len_dest++;
			i++;
		}
		dest[len_dest] = '\0';
	}
	return (sum);
}
