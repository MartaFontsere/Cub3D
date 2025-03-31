/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nex_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:31:47 by mfontser          #+#    #+#             */
/*   Updated: 2024/03/01 12:47:43 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*killer_text(char *string)
{
	free(string);
	return (NULL);
}

char	*gnl_strjoin(char *store, char *buffer)
{
	char	*fusion;
	int		i;
	int		j;

	i = 0;
	if (store == NULL)
	{
		store = malloc(sizeof(char) * 1);
		if (!store)
			return (NULL);
		store[0] = '\0';
	}
	fusion = malloc(sizeof(char) * (gnl_strlen(store) + gnl_strlen(buffer)
				+ 1));
	if (!fusion)
		return (killer_text(store));
	j = 0;
	while (store[i] != '\0')
		fusion[i++] = store[j++];
	j = 0;
	while (buffer[j] != '\0')
		fusion[i++] = buffer[j++];
	fusion[i] = '\0';
	free(store);
	return (fusion);
}

int	gnl_strlen(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}

int	check_store(char *store)
{
	int	i;

	i = 0;
	while (store[i] != '\0')
	{
		if (store[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
