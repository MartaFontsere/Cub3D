/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:37:53 by yanaranj          #+#    #+#             */
/*   Updated: 2025/01/31 18:46:44 by yanaranj         ###   ########.fr       */
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
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	len = i;
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] != '\0')
	{
		msg_error("Invalid path:\n", line);
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
	return (path);
}
/*verificar que no intentemos asignar una repetida*/
void	assign_path(char *line, t_map *map, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) && map->shader.err_flag == 0)
		map->shader.NO = cpy_path(line, map);
	else if (line[i] == 'S' && line[i + 1] == 'O' && ft_isspace(line[i + 2]) && map->shader.err_flag == 0)
		map->shader.SO = cpy_path(line, map);
	else if (line[i] == 'E' && line[i + 1] == 'A' && ft_isspace(line[i + 2]) && map->shader.err_flag == 0)
		map->shader.EA = cpy_path(line, map);
	else if (line[i] == 'W' && line[i + 1] == 'E' && ft_isspace(line[i + 2]) && map->shader.err_flag == 0)
		map->shader.WE = cpy_path(line, map);
	else
	{
		map->shader.err_flag = 1;
		return (msg_error("Invalid line: ", line));
	}
}

int	check_line(char *line, t_map *map)
{
	int	i;
	
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		assign_path(line, map, i);
	else if (line[i] == 'C' || line[i] == 'F')
		assign_color(line, &map->shader, i);//la i es la pos de C
	/* else if (line[i] == '1')
	{
		map->is_map = 1;	
		start_matrix();
	} */
	//printf("s_F:[%d]\n", map->shader.err_flag);
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
