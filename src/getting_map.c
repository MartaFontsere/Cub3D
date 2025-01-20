/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:28:37 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/20 20:41:16 by yanaranj         ###   ########.fr       */
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
		return (1);
	}
	return (0);
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
/*HAY QUE REDUCIR LINES*/
char	**complete_map(char *map_path, t_map *map)
{
	int		fd;
	int		pos;
	char	*line;
	char	**matrix_map;
	int		i;
	
	pos = count_fd_line(map_path, map);
	matrix_map = malloc(sizeof(char *) * (pos + 1));
	if (!matrix_map)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		free(matrix_map);
		exit_error("error opening file\n", 42);
	}
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	i = 0;
	while (line)
	{
		matrix_map[i] = ft_strdup(line);
		free(line);
		if (!matrix_map[i])
		{
			free_matrix(map);
			close(fd);
			return (NULL);
		}
		line = get_next_line(fd);
		i++;
	}
	matrix_map[i] = NULL;
	close(fd);
	free(line);
	return (matrix_map);
}

char    **get_final_map(int ac, char **av, t_map *map)
{
	//char	*raw_line = NULL;
	
    if (ac != 2 || check_name(av[1]) != 0)
		exit_error("Invalid arguments\n", 1);
		
	//raw_line = get_raw_map(av[1]);//aqui hace la lectura del fd
	map->my_map = complete_map(av[1], map);
	printf("%s", map->my_map[0]);
	printf("%s", map->my_map[1]);
	printf("%s", map->my_map[2]);
	
	/* if (!raw_line)
		exit_error("error getting raw map\n", 1);
	//map->raw_map = fill_void(raw_line);
	//printf("RAW\n%s\n", map->raw_map);
	map->my_map = ft_split(map->raw_map, '\n');

	if (!final_map(map->my_map, map, map->raw_map))
	{
		exit_error(RED"Invalid map2\n"END, 1);
		free(map->raw_map);
	}
	else
		printf(GREEN"This map es OK\n"END);
	free(map->raw_map); */
    return (map->my_map);
    //return (map->my_map);
}

/*	Para considerar un mapa cerrado, las paredes deben estar en la primera linea
	del fd, o rodeados de 0 en todas las direcciones.
*/
