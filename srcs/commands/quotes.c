/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:48:21 by anovelli          #+#    #+#             */
/*   Updated: 2022/11/22 17:16:48 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*remove_quotes_str_helper(char *str, int i)
{
	char	*temp;
	int		j;

	j = 0;
	temp = (char *)malloc(sizeof(char) * (int)ft_strlen(str) - i + 1);
	if (!temp)
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
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

char	*remove_quotes_str(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[j] != '\0')
	{
		if (str[j] == '\'')
			i++;
		j++;
	}
	if (i > 0)
		return (remove_quotes_str_helper(str, i));
	else
		return (str);
}
