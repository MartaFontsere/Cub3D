/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:49:06 by yanaranj          #+#    #+#             */
/*   Updated: 2025/02/04 16:16:52 by yanaranj         ###   ########.fr       */
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


/* int	count_fd_line(char *map_path, t_map *map)
{
	(void)map;
	
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
		if (line && line[0] == '1' && (line[0] != '\0' || line[0] != '\n'))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	printf("[%d]\n", count);
	return (count);
} */