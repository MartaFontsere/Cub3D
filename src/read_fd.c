/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/20 15:14:00 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_matrix(char *line, t_map *map)
{
	//int i;

	//i = 0;
	if (map->j == 0)
		map->tmp_matrix = malloc(sizeof(char *) * (map->c_height + 1));
	else
	{
		map->tmp_matrix = realloc(map->tmp_matrix, sizeof(char *) * \
		(map->c_height + 1));
		
	}
	if (!map->tmp_matrix)
		return (0);
	map->tmp_matrix[map->j] = cub_strdup(line, map->c_width);
	map->j++;
	map->tmp_matrix[map->j] = NULL;
	return (1);
}

void	assign_path(char *line, t_map *map, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !map->path.NO)
			map->path.NO = cpy_path(line, map);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !map->path.SO)
			map->path.SO = cpy_path(line, map);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]) \
	&& !map->path.EA)
			map->path.EA = cpy_path(line, map);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]) \
	&& !map->path.WE)
			map->path.WE = cpy_path(line, map);
	else
	{
		if (map->path.NO || map->path.SO || map->path.EA \
		|| map->path.WE)
			msg_error("There's a previus path assigned: ", line);
		else
			msg_error("Invalid line: ", line);
		map->path.err_flag = 1;
		return ;
	}
}

int	check_line(char *line, t_map *map, int i)
{
	while (ft_isspace(line[i]))//si no es mapa, go ahead
		i++;
	if (!curr_char(line[i], line, map))
		return (0);
	if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') \
	&& map->path.err_flag == 0 && map->is_map == 0)
		assign_path(line, map, i);
	else if ((line[i] == 'C' || line[i] == 'F') && map->path.err_flag == 0 \
	&& map->is_map == 0)
		assign_color(line, &map->path, i);
	else if (line[i] == '1' || (line [i] == '0'))
	{
		map->is_map = 1;
		map_control(line, map);
		map->c_height++;
	}
	if (line[i] == '\0' && map->is_map == 1)
		map->c_height++;
	if (map->path.err_flag == 1)
		return (0);
	if (map->is_map == 1 && (map->path.c_count + map->path.p_count) == 6)
	{
		if (!create_matrix(line, map))
			return (0);
	}
	return (1);
}

int	fd_is_correct(t_map *map)
{
	int		fd;
	char	*line;

	fd = open (map->fd_path, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open the file\n", 1);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (!check_line(line, map, 0))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (1);
}

int	read_file(int ac, char **av, t_map *map)
{
	map->fd_path = av[1];
	
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	if (!fd_is_correct(map) || map->path.p_count != 4)//te genera la matriz con el realloc
	{
		if (map->path.p_count != 4 && map->path.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		map->fd_path = NULL;
		return (0);
	}
	if (!get_final_map(map->tmp_matrix, map))
		return (0);
	return (1);
}