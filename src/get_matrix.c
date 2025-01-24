/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 18:32:21 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_rawmap(char *path, t_map *map)
{
	int		fd;
	char	*tmp_raw;
	char	*line;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open the file\n", 1);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	tmp_raw = malloc(sizeof(char *) + 1);
	if (!tmp_raw)
		return (free(line), NULL);//hay que liberar linea, no?
	tmp_raw[0] = '\0';
	tmp_raw = gnl_strjoin(tmp_raw, line);
	while (line)
	{
		map->line_size = ft_max_size(line, map->line_size);
		free(line);
		line = get_next_line(fd);
		if (line)
			tmp_raw = gnl_strjoin(tmp_raw, line);
	}
	close(fd);
	return (tmp_raw);
}

int	get_final_map(int ac, char **av, t_map *map)
{
	char	**cp_matrix;
	
	cp_matrix = NULL;
	map->fd_path = av[1];
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	map->rawmap = get_rawmap(map->fd_path, map);
	if (!map->rawmap)
		exit_error("Error getting map\n", 2);
	if (!min_chars(map->rawmap))
		exit_error("Invalid map\n", 42);
	cp_matrix = ft_split(map->rawmap,'\n');//LEAK
	if (!cp_matrix)
		return (0);
	print_matrix(cp_matrix, 2);//BORRAR
	if (!complete_matrix(cp_matrix, map))
		return (0);
    return (1);
}
