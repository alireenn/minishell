/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:48:21 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/11 18:41:39 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*remove_quotes_str(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while ((str[i] == '\"' || str[i] == '\'') && str[i] != '\0')
		i++;
	if (i > 0)
	{
		temp = (char *)malloc(sizeof(char) * (int)ft_strlen(str) - i + 1);
		if (!temp)
			return (str);
		i = 0;
		while (str[i])
		{
			if (str[i] == '\"' || str[i] == '\'')
				i++;
			else
			{
				temp[j] = str[i];
				j++;
				i++;
			}
		}
		temp[j] = '\0';
		return (temp);
	}
	else
		return (str);
}
