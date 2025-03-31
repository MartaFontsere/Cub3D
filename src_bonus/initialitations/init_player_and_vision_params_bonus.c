/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_and_vision_params_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:47:23 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/29 15:06:23 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	init_vision_params(t_game *gdata, t_vision *vision)
{
	vision->FOV.num_rays = gdata->map.px_width;
	vision->FOV.fov_rad = 60 * (M_PI / 180);
	vision->FOV.rays = malloc(sizeof(t_ray) * vision->FOV.num_rays);
	if (!vision->FOV.rays)
	{
		msg_error("Unable to allocate memory for FOV rays\n", NULL);
		clean_data(gdata);
		return (0);
	}
	return (1);
}

void	init_player_position(t_game *gdata, t_map *map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S'
				|| map->matrix[i][j] == 'E' || map->matrix[i][j] == 'W')
			{
				player->raw_x = j;
				player->raw_y = i;
			}
			j++;
		}
		i++;
	}
	player->x = (player->raw_x * gdata->minimap.px_in_cell_width)
		+ (gdata->minimap.px_in_cell_width / 2);
	player->y = (player->raw_y * gdata->minimap.px_in_cell_height)
		+ (gdata->minimap.px_in_cell_height / 2);
}

void	define_vision_angle(t_vision *vision, char orientation)
{
	if (orientation == 'N')
		vision->vision_angle = NORTH;
	else if (orientation == 'S')
		vision->vision_angle = SOUTH;
	else if (orientation == 'E')
		vision->vision_angle = EAST;
	else if (orientation == 'W')
		vision->vision_angle = WEST;
}

void	init_player_orientation(t_map *map, t_vision *vision)
{
	int	i;
	int	j;

	i = 0;
	while (map->matrix[i])
	{
		j = 0;
		while (map->matrix[i][j])
		{
			if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S'
				|| map->matrix[i][j] == 'E' || map->matrix[i][j] == 'W')
			{
				define_vision_angle(vision, map->matrix[i][j]);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	init_player_params(t_game *gdata, t_player *player)
{
	player->raw_x = 0;
	player->raw_y = 0;
	player->mov_right = 0;
	player->mov_left = 0;
	player->mov_up = 0;
	player->mov_down = 0;
	player->rotate_right = 0;
	player->rotate_left = 0;
	player->height = gdata->minimap.px_height / 2;
	player->radius = gdata->minimap.px_in_cell_width / 4;
	init_player_position(gdata, &gdata->map, player);
	init_player_orientation(&gdata->map, &gdata->vision);
}
