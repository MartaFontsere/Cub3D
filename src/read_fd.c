/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/13 22:12:25 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cpy_path(char *line, t_map *map)
{
	char	*tmp;
	char	*path;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = ft_strdup(ft_strchr(line, '.'));
	if (!tmp)
	{
		msg_error("A path does not exists: ", line);
		return ((map->path.err_flag = 1), NULL);
	}
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	len = i;
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] != '\0')
	{
		msg_error("Invalid path: ", line);
		map->path.err_flag = 1;
		return(free(tmp), NULL);
	}
	path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	len = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		path[len++] = tmp[i++];
	path[len] = '\0';
	free(tmp);
	map->path.p_count++;
	return (path);
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
		msg_error("Paths and colors are nor fully assigned yet\n", \
		"Cannot initialize map\n");
		return (0);
	}
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
		map->cells_width = ft_max_size(line, map->cells_width);
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
	if (line)
		free(line);
	close(fd);
	return (1);
}
