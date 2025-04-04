/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:59:52 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/04 03:21:09 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_image
{
	xpm_t			*xpm;
	mlx_image_t		*data;
}					t_image;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	char			**split;
	int				assigned;
	struct s_path	*path;
}					t_color;

typedef struct s_path
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*tmp_str;
	int				p_count;
	int				c_count;
	int				err_flag;
	t_color			c;
	t_color			f;
}					t_path;

typedef struct s_texture
{
	t_path			path;
	t_image			north_wall_img;
	t_image			south_wall_img;
	t_image			west_wall_img;
	t_image			east_wall_img;
	int				c_hex_color;
	int				f_hex_color;
}					t_texture;

typedef struct s_print
{
	double			wall_height;
	double			draw_wall_start;
	int				draw_wall_end;
	int				color;
	int				tex_x;
	double			tex_start_offset;
}					t_print;

typedef struct s_mlx
{
	mlx_t			*init;
	int				window_height;
	int				window_width;
	mlx_image_t		*image;
}					t_mlx;

typedef struct s_ray
{
	double			current_angle;
	double			dir_x;
	double			dir_y;
	double			first_dist_x;
	double			first_dist_y;
	double			other_dist_x;
	double			other_dist_y;
	int				check_ray_x_in_map;
	int				check_ray_y_in_map;
	int				x_sign;
	int				y_sign;
	int				line_crossing;
	int				cell_collision_x;
	int				cell_collision_y;
	double			px_collision_x;
	double			px_collision_y;
	double			diagonal_distance;
	double			perpendicular_distance;
}					t_ray;

typedef struct s_fov
{
	int				num_rays;
	double			fov_rad;
	t_ray			*rays;
}					t_fov;

typedef struct s_vision
{
	double			vision_angle;
	t_fov			fov;
	double			projection_factor;
	double			camera_height_scale;
}					t_vision;

typedef struct s_collision
{
	double			player_contour_x;
	double			player_contour_y;
	double			angle;
	double			angle_step;
}					t_collision;

typedef struct s_player
{
	int				height;
	int				raw_x;
	int				raw_y;
	double			x;
	double			y;
	double			cell_player_x;
	double			cell_player_y;
	double			radius;
	int				mov_right;
	int				mov_left;
	int				mov_up;
	int				mov_down;
	int				rotate_right;
	int				rotate_left;
	char			orientation;

}					t_player;

typedef struct s_minimap
{
	int				c_width;
	int				c_height;
	int				px_width;
	int				px_height;
	int				px_in_cell_width;
	int				px_in_cell_height;
	int				center_x;
	int				center_y;

}					t_minimap;

typedef struct s_map
{
	char			**matrix;
	char			**tmp_matrix;
	char			**void_matrix;
	char			*fd_path;
	int				is_map;
	int				j;
	int				init;
	int				open;
	int				px_width;
	int				px_height;
	int				c_width;
	int				c_height;
}					t_map;

typedef struct s_game
{
	t_texture		texture;
	t_player		player;
	t_map			map;
	t_minimap		minimap;
	t_vision		vision;
	t_collision		collision;
	t_print			print_map;
	t_mlx			mlx;
	int				finish_game;
}					t_game;

#endif