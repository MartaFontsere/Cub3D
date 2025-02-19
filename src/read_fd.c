/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/19 12:38:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	curr_char(int cur, char *line, t_map *map)
{
	int	counter;
	
	counter = map->path.c_count + map->path.p_count;
	if (cur != 'N' && cur != 'S' && cur != 'E' && cur != 'W' && cur != 'C' \
	&& cur != 'F' && cur != '1' && cur != '0' && cur != '\0' && cur != '\n')
	{
		map->path.err_flag = 1;
		msg_error("We can't process this line: ", line);
		return (0);
	}
	if ((cur == '1' || cur == '0') && counter != 6)
	{
		map->path.err_flag = 1;
		msg_error("Paths and colors are not fully assigned yet\n", \
		"Cannot initialize map\n");
		return (0);
	}
	return (1);
}

int	create_matrix(char *line, t_map *map)
{
	if (map->j == 0)
		map->tmp_matrix = malloc(sizeof(char *) * (map->cells_height + 1));
	else
		map->tmp_matrix = realloc(map->tmp_matrix, sizeof(char *) * (map->cells_height + 1));
	if (!map->tmp_matrix)
		return (0);
	//printf("F_W: [%zu]\n", map->cells_width);
	//printf(GREEN"%s"END, map->tmp_matrix[map->j]);
	map->tmp_matrix[map->j] = cub_strdup(line, map->cells_width);
	map->j++;
	map->tmp_matrix[map->j] = NULL;
	return (1);
}

int	check_line(char *line, t_map *map, int i)
{
	while (ft_isspace(line[i]))
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
		map->cells_height++;
		map->cells_width = ft_max_size(line, map->cells_width);//celda maxima
		//if (!map->cells_width)
		//	return (0);
	}
	if (line[i] == '\0' && map->is_map == 1)
		map->cells_height++;
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
	//printf(PURPLE"FINAL_line size: %zu\n"END, map->cells_width);
	if (line)
		free(line);
	close(fd);
	return (1);
}
