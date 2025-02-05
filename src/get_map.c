/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/05 16:48:14 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


/* char	**copy_map(char *line, t_map *map)
{
	char	**map_tmp;
	size_t	i;

	i = 0;
	map_tmp = malloc(sizeof(char*) * (map->map_height + 1));
	if (!map_tmp)
		return (NULL);
	while (i < map->map_height)
	{
		map_tmp[i] = ft_strdup(line);
		if (!map_tmp[i])
			return (free_matrix(map_tmp), NULL);
		i++;
	}
	map_tmp[i] = NULL;
	return (map_tmp);
} */

//iterador puede ser param
int	looking_map(char *line, t_map *map)
{
	int	i;

	i = 0;
	(void)map;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
	{
		printf("Is map\n");
	}
		//copy_map(line, map);
	return (1);
}


//Puedo agregar  en esta funcion para que encuentre la linea mas larga
int	init_map(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->fd_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (!looking_map(line, map))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (1);
}
//este clean_data me daba doble free
int	get_final_map(int ac, char **av, t_map *map)
{
	map->fd_path = av[1];
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	if (!fd_is_correct(map) || map->shader.p_count != 4)
	{
		if (map->shader.p_count != 4 && map->shader.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		//clean_data(map);
		map->fd_path = NULL;
		return (0);
	}
	printf("La altura del mapa es: [%zu]\n", map->map_height);
	if (map->is_map == 1)
	{
		if (!init_map(map))
			return (0);
	}
	return (1);
}
