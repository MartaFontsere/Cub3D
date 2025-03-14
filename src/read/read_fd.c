/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/13 23:37:08 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int	create_matrix(char *line, t_map *map)
{
	if (map->j == 0)
		map->tmp_matrix = malloc(sizeof(char *) * (map->c_height + 1));
	else
	{
		map->tmp_matrix = realloc(map->tmp_matrix, sizeof(char *) * \
		(map->c_height + 1));
	}
	if (map->c_height > 100)
		return (msg_error("Max height is 100. If you follow this rule\n", \
		"Dracarys team will thank you 🔥"), 0);
	if (!map->tmp_matrix)
		return (0);
	map->tmp_matrix[map->j] = cub_strdup(line, map->c_width);
	map->j++;
	map->tmp_matrix[map->j] = NULL;
	return (1);
}

void	assign_path(char *line, t_path *path, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !path->NO)
		path->NO = cpy_path(line, path, (i + 2));
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !path->SO)
		path->SO = cpy_path(line, path, (i + 2));
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]) \
	&& !path->EA)
		path->EA = cpy_path(line, path, (i + 2));
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]) \
	&& !path->WE)
		path->WE = cpy_path(line, path, (i + 2));
	else
	{
		if ((line[i] == 'N' && line[i + 1] != 'O') || (line[i] == 'S' \
		&& line[i + 1] != 'O') || (line[i] == 'W' && line[i + 1] != 'E') \
		|| (line[i] == 'E' && line[i + 1] != 'A'))
			msg_error("Invalid texture name: ", line);
		else if (path->NO || path->SO || path->EA || path->WE)
			msg_error("There's a previus path assigned: ", line);
		else
			msg_error("Invalid line: ", line);
		path->err_flag = 1;
		return ;
	}
}

int	check_line(char *line, t_path *path, t_map *map, int i)
{
	while (ft_isspace(line[i]))
		i++;
	curr_char(line[i], line, path);
	if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') \
	&& path->err_flag == 0 && (path->c_count + path->p_count) != 6)
		assign_path(line, path, i);
	else if ((line[i] == 'C' || line[i] == 'F') && path->err_flag == 0 \
	&& map->is_map == 0)
		assign_color(line, path, i);
	else if (line[i] == '1' || line [i] == '0' || line[i] == 'N' \
	|| line[i] == 'S' || line[i] == 'W' || line[i] == 'E' || (line[i] == '\0' \
	&& map->is_map))
	{
		map->is_map = 1;
		map_control(line, map, path);
		map->c_height++;
	}
	if (path->err_flag == 1)
		return (0);
	if (map->is_map == 1 && (path->c_count + path->p_count) == 6)
	{
		if (!create_matrix(line, map))
			return (0);
	}
	return (1);
}

int	fd_is_correct(t_game *gdata, t_map *map)
{
	int		fd;
	char	*line;

	fd = open (map->fd_path, O_RDONLY);
	if (fd < 0)
		exit_error("Cannot open the file\n", 42);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		if (!check_line(line, &gdata->texture.path, map, 0))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	if (map->is_map == 0)
		return (msg_error("Map is missing", "\n"), 0);
	return (1);
}

int	read_file(int ac, char **av, t_game *gdata)
{
	gdata->map.fd_path = av[1];
	if (ac != 2 || !check_name(gdata->map.fd_path))
		return (0);
	if (!fd_is_correct(gdata, &gdata->map) || gdata->texture.path.p_count != 4)
	{
		if (gdata->texture.path.p_count != 4 && gdata->texture.path.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		gdata->map.fd_path = NULL;
		return (0);
	}
	printf(RED"%u\n"END, gdata->map.c_height);
	if (!get_final_map(gdata->map.tmp_matrix, &gdata->map))
		return (0);
	return (1);
}
