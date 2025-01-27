/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/27 17:25:39 by yanaranj         ###   ########.fr       */
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
	(void)map;
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
	//count = 1;
	//printf(RED"%c\n"END, line[0]);
	while (line)
	{
		//map->map_width = ft_max_size(line, map->map_width); //lo tenemos tambien el get_rawmap
		count++;
		free(line);
		line = get_next_line(fd);
		//printf(PURPLE"%c\n"END, line[0]);
		//if (line && (line[0] != '\n' || line[0] != '\0'))
	}
	close(fd);
	free(line);
	//printf("[%d]\n", count);
	return (count);
}
