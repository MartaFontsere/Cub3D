/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:32:47 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/20 15:11:50 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_name(char *map_path)
{
	int	len;

	len = ft_strlen(map_path);
	if (ft_strncmp(map_path + len - 4, ".cub", 4) != 0)
	{
		printf("Invalid name map\n");
		return (0);
	}
	return (1);
}
//tengo que arreglarlo para que pille cualquier cosa del str
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
	//control de error
	i = 0;
	len = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		path[len++] = tmp[i++];
	path[len] = '\0';
	free(tmp);
	map->path.p_count++;
	return (path);
}

/*
	Si hay un char que no este permitido, bye
	Si parece que va a iniciar el mapa pero no hay los paths, bye
	
*/
int	curr_char(int cur, char *line, t_map *map)
{
	int	counter;

	counter = map->path.c_count + map->path.p_count;
	if (cur != 'N' && cur != 'S' && cur != 'E' && cur != 'W' && cur != 'C' \
	&& cur != 'F' && cur != '1' && cur != '0' && cur != '\0' && cur != '\n')
	{
		map->path.err_flag = 1;
		return (msg_error("We can't process this line: ", line), 0);
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
/*quiero comprobar los tabs en el mapa, ideferentemente de su pos*/
size_t	ft_max_size(char *line, size_t max)
{
	size_t	size;

	size = 0;
	while (line[size])
	{
		if (line[size] == '\t')
			return (msg_error("Tabs are an invalid char inside map", "\n"), 0);
		size++;
	}
	//printf("last max: %zu\n", max);
	if (max < size)
		max = size;
	//printf("new_max: %zu\n", max);
	//printf("char: %c\n", line[max - 3]);
	return (max);
}

void	map_control(char *line, t_map *map)
{
	int	i;

	i = 0;
	map->c_width = ft_max_size(line, map->c_width);
	if (!map->c_width)
	{
		map->path.err_flag = 1;
		return ;
	}
	while (line[i])
	{	
		if (map->is_map == 1 && (line[i] != 'N' && line[i] != 'S' && line[i] != 'W' \
			&& line[i] != 'E' && line[i] != '1'  && line[i] != '0' \
			&& line[i] != ' ' && line[i] != ' ' && line[i] != '\n'))
			{
				write(2, &line[i], 1);
				map->path.err_flag = 1;
				return (msg_error(": is an invalid char\n", NULL));
			}
		i++;
	}
}
