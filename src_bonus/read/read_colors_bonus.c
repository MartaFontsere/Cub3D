/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:08:22 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/06 19:12:21 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	get_colors(char *line, t_path *path, int i, char c)
{
	int	start;
	int	end;
	int	comma;

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
	if (c == 'C')
		cpy_colors(path->tmp_str, &path->c, -1);
	else if (c == 'F')
		cpy_colors(path->tmp_str, &path->f, -1);
	free(path->tmp_str);
}

void	get_color_path(char *line, t_color *color, int i)
{
	int	end;
	int	start;

	start = i;
	while (!ft_isspace(line[i]) && line[i])
		i++;
	end = i;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] != '\0')
	{
		color->path->err_flag = 1;
		return (msg_error(line, "The line must contain only one value\n"));
	}
	color->assigned = 1;
	color->is_path = 1;
	color->color_path = clean_str(line, start, (end - start), color->path);
	//color->path->c_count++;
}

void	control_c_values(char *line, t_path *path, int init_val, char c)
{
	if (path->c.assigned == 1)
	{
		path->err_flag = 1;
		return (msg_error("A celing value has already been assigned", "\n"));
	}
	if (ft_isdigit(line[init_val]))
		get_colors(line, path, init_val, c);
	else if (ft_isalpha(line[init_val]))
		get_color_path(line, &path->c, init_val);
	else
	{
		path->err_flag = 1;
		return (msg_error("There's not a valid value for C\n", "Try again\n"));
	}
}

void	control_f_values(char *line, t_path *path, int init_val, char f)
{
	if (path->f.assigned == 1)
	{
		path->err_flag = 1;
		return (msg_error("A floor value has already been assigned", "\n"));
	}
	if (ft_isdigit(line[init_val]))
		get_colors(line, path, init_val, f);
	else if (ft_isalpha(line[init_val]))
		get_color_path(line, &path->f, init_val);
	else
	{
		path->err_flag = 1;
		return (msg_error("There's not a valid value for F\n", "Try again\n"));
	}
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
	if (line[init] == 'C')
		control_c_values(line, path, i, line[init]);
	else if (line[init] == 'F')
		control_f_values(line, path, i, line[init]);
	if (path->err_flag == 1)
		return ;
	if (path->c_count == 2 && (!path->c.assigned || !path->f.assigned))
	{
		path->err_flag = 1;
		if (!path->f.assigned || !path->c.assigned)
			return (msg_error("Some colors are missing", "\n"));
	}
}
