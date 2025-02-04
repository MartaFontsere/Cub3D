/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/04 14:29:40 by yanaranj         ###   ########.fr       */
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
		map->shader.err_flag = 1;
		return (NULL);
	}
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	len = i;
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] != '\0')
	{
		msg_error("Invalid path: ", line);
		map->shader.err_flag = 1;
		return(free(tmp), NULL);
	}
	path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	len = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		path[len++] = tmp[i++];
	path[len] = '\0';
	free(tmp);
	map->shader.count++;
	return (path);
}

void	assign_path(char *line, t_map *map, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !map->shader.NO)
			map->shader.NO = cpy_path(line, map);//creo que es mas efectivo si ponemos el path
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) \
	&& !map->shader.SO)
			map->shader.SO = cpy_path(line, map);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]) \
	&& !map->shader.EA)
			map->shader.EA = cpy_path(line, map);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]) \
	&& !map->shader.WE)
			map->shader.WE = cpy_path(line, map);
	else
	{
		if (map->shader.NO || map->shader.SO || map->shader.EA \
		|| map->shader.WE)
			msg_error("There's a previus path assigned: ", line);
		else
			msg_error("Invalid line: ", line);
		map->shader.err_flag = 1;
		return ;
	}
}

int	check_line(char *line, t_map *map)
{
	int	i;
	char	cur;
	
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	cur = line[i];
	if (cur != 'N' && cur != 'S' && cur != 'E' && cur != 'W' && cur != 'C' \
	&& cur != 'F' && cur != '\0' && cur != '1')
		return (msg_error("We can't process this line: ", line), 0);
	if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') \
	&& map->shader.err_flag == 0)
		assign_path(line, map, i);
	else if ((line[i] == 'C' || line[i] == 'F') && map->shader.err_flag == 0)
		assign_color(line, &map->shader, i);//la i es la pos de C
	else if (line[i] == '1' || line [i] == '0')
		start_map(line, map, i);
	if (map->shader.err_flag == 1)
		return (0);
	return (1);
}

/*unica lectura del fd para conseguir los params de las structs*/
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
		if (!check_line(line, map))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	return (1);
}
