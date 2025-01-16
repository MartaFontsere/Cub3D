/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:31:32 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/16 15:57:33 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_store(char *store)
{
	char	*new_store;
	int		i;
	int		j;

	i = 0;
	while (store[i] != '\n' && store[i] != '\0')
		i++;
	if (store[i] == '\n')
		i++;
	if (store[i] == '\0')
		return (killer_text(store));
	j = gnl_strlen(store);
	new_store = malloc(sizeof(char) * (j - i + 1));
	if (!new_store)
		return (killer_text(store));
	j = 0;
	while (store[i] != '\0')
	{
		new_store[j] = store[i];
		i++;
		j++;
	}
	new_store[j] = '\0';
	free (store);
	return (new_store);
}

char	*construct_line(char *store)
{
	char	*line;
	int		i;

	i = 0;
	while (store[i] != '\n' && store[i] != '\0')
		i++;
	if (store[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (store[i] != '\n' && store[i] != '\0')
	{
		line[i] = store[i];
		i++;
	}
	if (store[i] == '\n')
	{
		line [i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*fill_store(int fd, char *store)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (killer_text(store));
	bytes = 1;
	while (bytes > 0 && (!store || check_store(store) == 0))
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (killer_text(store));
		}
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			store = gnl_strjoin(store, buffer);
		}
	}
	free (buffer);
	return (store);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!store || check_store(store) == 0)
	{
		store = fill_store(fd, store);
	}
	if (!store)
		return (NULL);
	line = construct_line(store);
	if (!line)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	store = update_store(store);
	return (line);
}

