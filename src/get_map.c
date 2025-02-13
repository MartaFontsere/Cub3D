/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/13 12:50:07 by yanaranj         ###   ########.fr       */
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
/* 
//iterador puede ser param
int	looking_map(char *line, t_map *map)
{
	int	i;

	i = 0;
	map->tmp_matrix = malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->tmp_matrix)
		return (0);
	while (line[i] == '\t' || line[i] == ' ')
		i++;
	//printf("line[%d]\n", i);
	if (line[i] == '1' || line[i] == '0')
	{
		printf("a map was found\n");
		map->is_map = 1;
	}
	if (map->is_map == 1)
	{
		if (line[i] == '\0')
			map->tmp_matrix[map->j] = ft_strdup("");
		else
			map->tmp_matrix[map->j] = ft_strdup(line);
		//printf(PURPLE"%d - %s\n"END, map->j, map->tmp_matrix[map->j]);
		map->j++;
		//map->tmp_matrix[map->j] = NULL;
	}
	if (!map->tmp_matrix)
	{
		free_matrix(map->tmp_matrix);
		return (0);
	}
	if ((size_t)map->j >= map->map_height)
	{
		map->tmp_matrix[map->j] = NULL;
	}
	//if (map->is_map == 1)
	//	printf(RED"%d - %s\n"END, (map->j - 1), map->tmp_matrix[map->j - 1]);
	return (1);
}


//Puedo agregar  en esta funcion para que encuentre la linea mas larga
int	init_map(t_map *map)
{
	int		fd;
	char	*line;

	map->is_map = 0;//reiniciamos la flag de map
	fd = open(map->fd_path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	int	i = 0;
	while (line)
	{  
		if (!looking_map(line, map))
		{
			free(line);
			close(fd);
			return (0);
		}
		if (map->is_map == 1)
			printf(CYAN"%s\n"END, map->tmp_matrix[i]);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	//printf(CYAN"%s\n"END, map->tmp_matrix[2]);
	//print_matrix(map->tmp_matrix, 1);
	//if (line)
	//	free(line);
	close(fd);
	return (1);
} */

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
		map->fd_path = NULL;
		return (0);
	}
	//print_matrix(map->tmp_matrix, 1);
	return (1);
}

int	create_matrix(char *line, t_map *map, int i)
{
	(void)i;
	printf(RED"%zu\t"END, map->map_height);
	printf(RED"%d\n"END, map->j);
	if (map->j == 0)
		map->tmp_matrix = malloc(sizeof(char *) * (map->map_height + 1));
	else
		map->tmp_matrix = realloc(map->tmp_matrix, sizeof(char *) * (map->map_height + 1));
	if (!map->tmp_matrix)
		return (0);
	map->tmp_matrix[map->j] = ft_strdup(line);
	map->j++;
	map->tmp_matrix[map->j] = NULL;
	return (1);
}
