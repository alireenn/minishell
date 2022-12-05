/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovelli <anovelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:48:21 by anovelli          #+#    #+#             */
/*   Updated: 2022/12/05 17:49:35 by anovelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*remove_quotes_str_helper(char *str, int i)
{
	char	*temp;
	int		j;
	char	open;

	j = 0;
	temp = (char *)malloc(sizeof(char) * ((int)ft_strlen(str) - i + 1));
	if (!temp)
		return (str);
	i = 0;
	open = '\0';
	while (str[i])
	{
		if (str[i] == open)
		{
			open = '\0';
			i++;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && open == '\0')
			open = str[i++];
		else
			temp[j++] = str[i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*remove_quotes_str(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[j] != '\0')
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			i += 2;
			j = search_closing(str, j, str[j], str[j]) - 1;
		}
		j++;
	}
	tmp = ft_strdup(str);
	if (i > 0)
		return (remove_quotes_str_helper(str, i));
	return (ft_strdup(str));
}
