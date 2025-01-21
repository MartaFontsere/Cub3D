/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:28:37 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/21 20:18:06 by yanaranj         ###   ########.fr       */
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
	char	*line;
	char	**matrix_map;//usamos la var de la struct??
	int		i;
	
	map->fd_lines = count_fd_line(map_path, map);//podemos hacer un save malloc
	matrix_map = malloc(sizeof(char *) * (map->fd_lines + 1));
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
			free_matrix(matrix_map);
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

/*tenemos que retornar el my_map que ya debe tener todos los espacios llenos*/
char    **get_final_map(int ac, char **av, t_map *map)
{
	int	i;
	int	j;
	char	**cp_matrix;

	i = 0;
	j = 0;
    if (ac != 2 || check_name(av[1]) != 0)
		exit_error("Invalid arguments\n", 1);	
	/*check la raw line*/
	map->my_map = complete_map(av[1], map);
	cp_matrix = malloc(sizeof(char *) * (map->fd_lines + 1));
	if (!cp_matrix)
		return (NULL);
	while (map->my_map[i])
		cp_matrix[j++] = fill_void(map->my_map[i++], map);
	cp_matrix[j] = NULL;
	//ahora tenemos que rellenar el mapa con los chars del mapa original
	//lo podemos borrar
	j = 0;
	while (cp_matrix[j])
	{
		printf("%s\n", cp_matrix[j]);
		j++;
	}
    return (cp_matrix);
}
