/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:32:47 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/21 13:38:45 by yanaranj         ###   ########.fr       */
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

char	*cpy_path(char *line, t_path *path, int pos)
{
	char	*tmp;
	int		i;
	int		end;

	while (ft_isspace(line[pos]))
		pos++;
	if (line[pos] == '\0')
	{
		msg_error("Path is not found: ", line);
		return ((path->err_flag = 1), NULL);
	}
	else
		tmp = ft_strdup(ft_strchr(line, line[pos]));
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	end = i;
	while (ft_isspace(tmp[i]))
		i++;
	if (tmp[i] != '\0' && tmp[i] != '\n')
	{
		msg_error(tmp, ": is not a valid path");
		free(tmp);
		return ((path->err_flag = 1), NULL);
	}
	tmp = clean_str(tmp, end, path);
	return (tmp);
}

int	curr_char(int cur, char *line, t_path *path)
{
	int	counter;

	if (cur == '#' || cur == '/')
		return (1);
	counter = path->c_count + path->p_count;
	if (cur != 'N' && cur != 'S' && cur != 'E' && cur != 'W' && cur != 'C' \
	&& cur != 'F' && cur != '1' && cur != '0' && cur != '\0' && cur != '\n')
	{
		path->err_flag = 1;
		return (msg_error("We can't process this line: ", line), 0);
	}
	if ((cur == '1' || cur == '0') && counter != 6)
	{
		path->err_flag = 1;
		msg_error("Paths and colors are not fully assigned yet\n", \
		"Cannot initialize map\n");
		return (0);
	}
	return (1);
}

int	ft_max_size(char *line, int max)
{
	int	size;

	size = 0;
	while (line[size])
	{
		if (line[size] == '\t')
			return (msg_error("Tabs are an invalid char inside map", "\n"), 0);
		size++;
	}
	if (max < size)
		max = size;
	return (max);
}

void	map_control(char *line, t_map *map, t_path *path)
{
	int	i;

	i = 0;
	map->is_map = 1;
	map->c_width = ft_max_size(line, map->c_width);
	if (!map->c_width || map->c_width > 120)
	{
		msg_error("Max width is 120. If you follow this rule\n", \
		"		DrackyTeam will thank you🔥\n");
		path->err_flag = 1;
		return ;
	}
	while (line[i])
	{
		if (map->is_map == 1 && (line[i] != 'N' && line[i] != 'S' \
		&& line[i] != 'W' && line[i] != 'E' && line[i] != '1' \
		&& line[i] != '0' && line[i] != ' ' && line[i] != '\n' \
		&& line[i] != 'D'))
		{
			path->err_flag = 1;
			ft_write(2, &line[i], 1);
			return (msg_error(": is an invalid char\n", NULL));
		}
		i++;
	}
}
