/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:28:37 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/24 13:02:49 by yanaranj         ###   ########.fr       */
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

char	**extract_matrix(char *fd_path, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	char	**cp_matrix;

	fd =  open(fd_path, O_RDONLY);
	if (fd < 0)
		exit_error("error opening file\n", 42);
	map->fd_lines = count_fd_line(fd_path, map);
	cp_matrix = malloc(sizeof(char *) * (map->fd_lines + 1));
	if (!cp_matrix)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	i = 0;
	while (line) 
	{
		cp_matrix[i] = ft_strdup(line);
		free(line);
		if (!cp_matrix[i++])
		{
			free_matrix(cp_matrix);
			return (close(fd), NULL);
		}
		line = get_next_line(fd);
	}
	cp_matrix[i] = NULL;
	close(fd);
	free(line);
	return (cp_matrix);
}

//como guardamos el resultado en la matriz de la struct, podemos ponerlo a int y asi
//liberar en el main
char	**get_final_map(int ac, char **av, t_map *map)
{
	//int	i;
	//int	j;
	char	**cp_matrix;//tmp
	
	cp_matrix = NULL;
	if (ac != 2 || check_name(av[1]) != 0)
			exit_error("Invalid arguments\n", 1);
	cp_matrix = extract_matrix(av[1], map);//no es la final
	if (!cp_matrix)
		return (NULL);
	if (!min_chars(cp_matrix))
		return (NULL);
	/* if (!get_rawline(cp_matrix, map))
		return (NULL); */
	return (cp_matrix);
}
