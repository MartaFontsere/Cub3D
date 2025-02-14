/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:04:50 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/14 18:38:39 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*cub_strdup(char *s1, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;
	int		tabs;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		if (s1[i] == '\t')
		{
			tabs = 4;
			while (tabs--)
				str[j++] = '-';
			i++;
		}
		else
			str[j++] = s1[i++];
	}
	str[j] = '\0';
	//printf("END: [%zu]\n", j);
	//printf("[%c]\n", str[j]);
	//printf(RED"STR:\n%s\n"END, str);
	return (str);
}

//me crea la matriz y hace un realloc a medida que se actualiza la altura del mapa
int	create_matrix(char *line, t_map *map)
{
	if (map->j == 0)
		map->tmp_matrix = malloc(sizeof(char *) * (map->cells_height + 1));
	else
		map->tmp_matrix = realloc(map->tmp_matrix, sizeof(char *) * (map->cells_height + 1));
	if (!map->tmp_matrix)
		return (0);
	map->tmp_matrix[map->j] = cub_strdup(line, map->cells_width);
	map->j++;
	map->tmp_matrix[map->j] = NULL;
	return (1);
}

int	get_final_map(int ac, char **av, t_map *map)
{
	map->fd_path = av[1];
	if (ac != 2 || !check_name(map->fd_path))
		return (0);
	if (!fd_is_correct(map) || map->path.p_count != 4)
	{
		if (map->path.p_count != 4 && map->path.err_flag == 0)
			msg_error("A path is missing\n", NULL);
		map->fd_path = NULL;
		return (0);
	}
	printf("\n");
	if (!complete_matrix(map->tmp_matrix, map))
		return (0);
	return (1);
}


