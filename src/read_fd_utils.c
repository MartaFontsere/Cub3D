/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:32:47 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/19 11:50:47 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cpy_path(char *line, t_map *map)
{
	char	*tmp;
	char	*path;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = ft_strdup(ft_strchr(line, '.'));
	if (!tmp)
	{
		msg_error("A path does not exists: ", line);
		return ((map->path.err_flag = 1), NULL);
	}
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	len = i;
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] != '\0')
	{
		msg_error("Invalid path: ", line);
		map->path.err_flag = 1;
		return(free(tmp), NULL);
	}
	path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	len = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		path[len++] = tmp[i++];
	path[len] = '\0';
	free(tmp);
	map->path.p_count++;
	return (path);
}

char	*cub_strdup(char *s1, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}

size_t	ft_max_size(char *line, size_t max)
{
	size_t	size;
	int		tabs;

	size = 0;
	tabs = 0;
	while (line[size])
	{
		if (line[size] == '\t')
			return (msg_error("Tabs are invalid char inside map\n", NULL), 0);
		size++;
	}
	//printf("last max: %zu\n", max);
	if (max < size)
		max = size;
	//printf("new_max: %zu\n", max);
	//printf("char: %c\n", line[max - 3]);
	return (max);
}