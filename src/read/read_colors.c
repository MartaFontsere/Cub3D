/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:08:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/04 13:03:50 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**split_color(char *rgb, t_color *color)
{
	char	**result;
	
	if (color->assigned)
	{
		color->path->err_flag = 1;
		return(msg_error("Color is already assigned\n", NULL), NULL);
	}
	result = ft_split(rgb, ',');
	if ((!result[0] || !result[1] || !result[2]))
	{
		color->path->err_flag = 1;
		free_matrix(result);
		return (msg_error("Invaid split\n", rgb), NULL);
	}
	return (result);
}

void	cpy_colors(char *rgb, t_color *color, int i)
{
	char	**split;
	
	split = split_color(rgb, color);
	if (!split)
		return ;
	while (split[++i])
	{
		if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 0)
			color->r = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 1)
			color->g = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 2)
			color->b = ft_atoi(split[i]);
		else
		{
			color->path->err_flag = 1;
			return (msg_error("Out of range: ", split[i]), free_matrix(split));
		}
	}
	color->assigned = 1;
	color->path->c_count++;
	free_matrix(split);
}

void	get_colors(char *line, t_path *path, int i, int init)
{
	int		start;
	int		end;
	int		comma;

	comma = 0;
	start = i + 1;
	while (ft_isdigit(line[++i]) || line[i] == ',')
	{
		if (line[i] == ',')
			comma++;
	}
	end = i;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0' || comma != 2)
	{
		path->err_flag = 1;
		return (msg_error("This RGB is not valid: ", line));
	}
	path->tmp_str = ft_substr(line, start, end - 2);
	if (line[init] == 'C')
		cpy_colors(path->tmp_str, &path->c, -1);
	else if (line[init] == 'F')
		cpy_colors(path->tmp_str, &path->f, -1);
	free(path->tmp_str);
}

void	assign_color(char *line, t_path *path, int i)
{
	int	init;

	init = i;
	if ((line[i] == 'C' || line[i] == 'F') && ft_isspace(line[i + 1]))
		i++;
	else
	{
		path->err_flag = 1;
		return (msg_error(line, "This format of line is incorrect"));
	}
	while (ft_isspace(line[i]))
		i++;
	if (ft_isalpha(line[i]))
	{
		path->err_flag = 1;
		return (msg_error("A path for floor or celing is forbidden: ", line));
	}
	get_colors(line, path, i - 1, init);
	if (path->c_count == 2 && (!path->c.assigned || !path->f.assigned))
	{
		path->err_flag = 1;
		if (!path->f.assigned || !path->c.assigned)
			return (msg_error("Some colors are missing", "\n"));
	}
}
