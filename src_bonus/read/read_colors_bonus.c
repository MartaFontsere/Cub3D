/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:08:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:29 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	cpy_colors(char *rgb, t_color *color, int i)
{
	char	**split;

	split = ft_split(rgb, ',');
	if (!split[0] || !split[1] || !split[2])
	{
		color->path->err_flag = 1;
		return (free_matrix(split), msg_error("Invaid split\n", NULL));
	}
	while (split[++i])
	{
		if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 0)
			color->R = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 1)
			color->G = ft_atoi(split[i]);
		else if ((ft_atoi(split[i]) >= 0 && ft_atoi(split[i]) <= 255) && i == 2)
			color->B = ft_atoi(split[i]);
		else
		{
			color->path->err_flag = 1;
			return (msg_error("Invalid value: ", split[i]), free_matrix(split));
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
	path->tmp_str = ft_substr(line, start, end);
	if (line[init] == 'C')
		cpy_colors(path->tmp_str, &path->C, -1);
	else if (line[init] == 'F')
		cpy_colors(path->tmp_str, &path->F, -1);
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
	if (!ft_isdigit(line[i]))
	{
		path->err_flag = 1;
		return (msg_error("A path for floor or celing is forbidden: ", line));
	}
	if (path->c_count < 2)
		get_colors(line, path, i - 1, init);
	if (path->c_count == 2 && (!path->C.assigned || !path->F.assigned))
	{
		path->err_flag = 1;
		if (!path->F.assigned || !path->C.assigned)
			return (msg_error("Some colors are missing", "\n"));
	}
}
