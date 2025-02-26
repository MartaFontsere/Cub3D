/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 03:47:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoinchar(char *str, char c)
{
	int		i;
	char	*new_str;

	if (str == NULL && c == '\0')
		return (NULL);
	if (str)
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 1 + 1));
	else
		new_str = malloc(sizeof(char) * (1 + 1));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str && str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}
