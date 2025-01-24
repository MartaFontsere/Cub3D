/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 17:38:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_name(char *map_path)
{
	char	*ext;

	ext = ft_strchr(map_path, '.');

	if (ft_strncmp(ext, ".cub", 4) != 0)
	{
		printf("Invalid name map\n");
		return (0);
	}
	return (1);
}

int	min_chars(char *rawmap)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rawmap[i])
	{
		if (rawmap[i] != 'N' && rawmap[i] != 'S' && rawmap[i] != 'E'\
		&& rawmap[i] != 'W' && rawmap[i] != '1' && rawmap[i] != '0'\
		&& rawmap[i] != '\n' && rawmap[i] != ' ')
			return (0);
		if (rawmap[i] == 'N' || rawmap[i] == 'S' || rawmap[i] == 'E'\
		|| rawmap[i] == 'W')
			count++;
		i++;
	}
	if (count != 1)
	{
		printf(RED"players: [%d]\n"END, count);
		return (0);
	}
	return (1);
}

size_t	ft_max_size(char *line, size_t max)
{
	size_t	size;

	size = ft_strlen(line) - 1;
	if (max < size)
		max = size;
	return (max);
}

int	count_fd_line(char *map_path, t_map *map)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		exit_error("error opening file\n", 42);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		map->line_size = ft_max_size(line, map->line_size);
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (count);
}