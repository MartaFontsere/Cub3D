/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:28:37 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/17 16:12:05 by yanaranj         ###   ########.fr       */
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
char	*fill_void(char *raw_map)
{
	int i;

	i = 0;
	while (raw_map[i])
	{
		if (raw_map[i] == ' ' || raw_map[i] == '\t')
			raw_map[i] = '5';
		i++;
	}
	return (raw_map);
}

/*	Debemos sustituir el los esp o tabs por '0', de esta manera tenemos un mapa 
	rectangular y evitamos tener segf. Lo necesitamos para el floodfill
	Esta funcion seria como el main del gnl
*/
char	*get_raw_map(char *map_path)
{
	int	fd;
	char	*line;
	char *raw_map;
	
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		exit_error("error opening file\n", 42);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	raw_map = malloc(sizeof(char *) * 1);
	if (!raw_map)
		return (NULL);
	raw_map[0] = '\0';
	while (line)
	{
		raw_map = gnl_strjoin(raw_map, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	return (raw_map);
}

char    **get_final_map(int ac, char **av, t_map *map)
{
	char	*raw_line;
	
    if (ac != 2 || check_name(av[1]) != 0)
		exit_error("Invalid arguments\n", 1);
	raw_line = get_raw_map(av[1]);//le pasamos el path del fd del map
	if (!raw_line)
		exit_error("error getting map\n", 1);
	map->raw_map = fill_void(raw_line);
	printf("RAW\n%s\n", map->raw_map);
	map->my_map = ft_split(map->raw_map, '\n');

	/*parseo de los chars del mapa*/
	if (!final_map(map->my_map, map, map->raw_map))
	{
		exit_error(RED"Invalid map2\n"END, 1);
		free(map->raw_map);
	}
	else
		printf(GREEN"This map es OK\n"END);
	free(map->raw_map);
    return (map->my_map);
}

/*	Para considerar un mapa cerrado, las paredes deben estar en la primera linea
	del fd, o rodeados de 0 en todas las direcciones.
*/
