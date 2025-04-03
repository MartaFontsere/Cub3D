/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 12:03:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libs/get_next_line/get_next_line.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "structs_bonus.h"


/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define GREEN "\e[1;92m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define TURQUOISE "\e[1;38;5;80m"
# define PINK "\e[1;38;5;213m"
# define FUCSIA "\e[1;38;5;201m"
# define PURPLE "\e[1;38;5;135m"
# define CYAN "\e[1;96m"
# define LIME_GREEN "\e[1;38;5;118m"
# define ORANGE "\e[1;38;2;255;128;0m"


/*MLXCOLORS*/
# define BLACK 0x00000080
# define DARK_GREY 0x3C3C3CFF
# define MEDIUM_GREY 0X69696980
# define SOFT_GREY 0x959595FF
# define RED1 0xFF0000FF
# define YELLOW1 0xFFC006FF
# define SOFT_YELLOW 0xFEF4D3FF
# define BLUE1 0X9AC4FFFF


			/*TEXTURES*/ //LUEGO BORRAR PATHS, PARA MIENTRAS SIN PARSING
			#define NORTH_TEXTURE "textures/map_walls/opcion2/Norte.xpm42"
			#define SOUTH_TEXTURE "textures/map_walls/opcion2/Sur.xpm42"
			#define WEST_TEXTURE "textures/map_walls/opcion2/Oeste.xpm42"
			#define EAST_TEXTURE "textures/map_walls/opcion2/Este.xpm42"

			//esto no borrar:
			// #define SKY_TEXTURE "textures/sky/Sky_10.xpm42"
			#define SKY_TEXTURE "textures/sky/Sky_10.xpm42"
			#define FLOOR_TEXTURE "textures/floor/Floor5.xpm42"
			#define DOOR_TEXTURE "textures/door/Door2.xpm42"
			#define DRAGON_1 "textures/flying_dragon/dragon1.xpm42"
			#define DRAGON_2 "textures/flying_dragon/dragon2.xpm42"
			#define DRAGON_3 "textures/flying_dragon/dragon3.xpm42"
			#define DRAGON_WIDTH 380
			#define DRAGON_HEIGHT 213



/*PLAYER ORIENTATION*/
# define NORTH M_PI_2
# define SOUTH 3 * M_PI_2
# define EAST 0
# define WEST M_PI



/*MOVE*/
# define MOVE_RIGHT 0
# define MOVE_LEFT 1
# define MOVE_UP 2
# define MOVE_DOWN 3

/*PLAYER SPEED*/
# define MOVE_SPEED 4 // cuantos pixeles se mueve cada vez que tocamos una tecla
# define ROTATION_SPEED 0.06

/*MAP*/
#define MAP_PX_WIDTH 2560
#define MAP_PX_HEIGHT 1440



// //BORRAR, ESTARA EN EL PARSING
// #define CEELING_R 154
// #define CEELING_G 196
// #define CEELING_B 255
// #define FLOOR_R 88
// #define FLOOR_G 134
// #define FLOOR_B 80


/*MINIMAP*/
#define MINIMAP_PX_WIDTH 515
#define MINIMAP_PX_HEIGHT 340
#define MINIMAP_PX_CELL_WIDTH 24
#define MINIMAP_PX_CELL_HEIGHT 24

#define DOOR_START_OPEN_DISTANCE 2.2 // distancia en casillas
#define DOOR_END_OPEN_DISTANCE 1.4


//-------------------------------------------------
//					MAIN
//-------------------------------------------------
void	close_window(t_game	*gdata);
int		main(int ac, char **av);

//-------------------------------------------------
//					READ
//-------------------------------------------------

/*READ_FD*/
int		create_matrix(char *line, t_map *map);
void	assign_path(char *line, t_path *path, int i);
int		check_line(char *line, t_path *path, t_map *map, int i);
int		fd_is_correct(t_game *gdata, t_map *map);
int		read_file(int ac, char **av, t_game *gdata, t_map *map);

/*READ_FD_UTILS*/
int		check_name(char *map_path);
char	*cpy_path(char *line, t_path *path, int pos, int i);
int		curr_char(int cur, char *line, t_path *path);
int		ft_max_size(char *line, int max);
void	map_control(char *line, t_map *map, t_path *path, int i);

/*READ_FD-UTILS2*/
char	*clean_str(char *src, int start, int end, t_path *path);

/*READ_COLORS*/
void	get_colors(char *line, t_path *path, int i, char c);
void	get_color_path(char *line, t_color *color, int i);
void	control_c_values(char *line, t_path *path, int init_val, char c);
void	control_f_values(char *line, t_path *path, int init_val, char c);
void	assign_color(char *line, t_path *path, int i);

/*READ_COLORS_UTILS*/
void	cpy_colors(char *rgb, t_color *color, int i);

/*GET_MAP*/
char	*cub_strdup(char *s1, int len);
char	**copy_map(char **map, int height);
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);

//------------------------------------------------
//					PARSE
//------------------------------------------------

/*PARSE_DOOR*/
int	check_y_pos(int i, int j, t_map *map);
int	check_x_pos(int i, int j, t_map *map);
int	is_door(int i, int j, t_map *map);

/*PARSE_MAP*/
int		check_borders(char **matrix, int i, t_map *map);
int		is_close(char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		parse_map(t_game *gdata, char **matrix, t_map *map);

/*PARSE_UTILS*/
void	check_n_line(char **src, t_map *map);
int		check_esp(int x, int y, t_map *map);
int		check_zero(int i, int j, t_map *map);
int		check_player(int i, int j, t_map *map);

//------------------------------------------------
//					INITIALITATIONS
//------------------------------------------------

/*INITIALITATIONS*/
int		init_gdata_values(t_game *gdata);

/*INIT_MAP_MINIMAP_PARAMS*/
void 	init_map_params (t_game *gdata, t_map *map);
void	init_minimap_params(t_game *gdata);

/*INIT_PLAYER_AND_VISION_PARAMS*/
void 	init_player_params (t_game *gdata, t_player *player);
void	init_player_orientation(t_map *map, t_vision *vision, t_player *player);
void	define_vision_angle(t_vision *vision, char orientation);
void	init_player_position(t_game *gdata, t_map *map_info, t_player *player);
int 	init_vision_params (t_game *gdata, t_vision *vision);

/*INIT_MLX_PARAMS*/
int		init_mlx(t_game *gdata, t_mlx *mlx);
int		create_new_images(t_game *gdata, t_mlx *mlx);
int		put_image_to_window(t_game *gdata, t_mlx *mlx);

/*INIT_TEXTURES_COLORS*/
void 	init_textures_and_colors_path(t_texture *texture, t_path *path);
void	init_textures(t_texture *texture, t_path *path);
void	init_colors(t_path *path);


//------------------------------------------------
//					WALLS_RAYCASTING
//------------------------------------------------

/*CALCULATE_FOV*/
void	calculate_fov(t_game *gdata, double x, double y);

/*CALCULATE_RAY*/
void 	calculate_ray(t_game *gdata, t_ray *ray, double x, double y);
void 	find_ray_distance_and_collision_point(t_ray *ray, t_game *gdata, double x, double y);
void 	traverse_ray_until_hit(t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map);
void 	init_ray_direction (t_ray *ray, t_game *gdata, int check_ray_x_in_map,  int check_ray_y_in_map);

/*CALCULATE_RAY_UTILS*/
void 	prepare_vertical_final_collision_params (t_ray *ray, t_game *gdata, double x);
void 	prepare_horizontal_final_collision_params (t_ray *ray, t_game *gdata, double y);
void 	controll_x_limit_case (t_ray *ray, int check_ray_x_in_map, double cell_player_x);
void 	controll_y_limit_case (t_ray *ray, int check_ray_y_in_map, double cell_player_y);
double 	compute_collision_coordinate(int check_ray_coord, int ray_sign, double px_in_cell_size);



void check_matrix_lines (t_ray *ray, int *check_ray_x_in_map, int *check_ray_y_in_map);


//------------------------------------------------
//					FLOOR_RAYCASTING
//------------------------------------------------


//------------------------------------------------
//					DOORS_RAYCASTING
//------------------------------------------------

/*CHECK_RAY_OPENED_DOOR*/
int should_block_ray(t_ray *ray, t_game *gdata, int map_x, int map_y);
int convert_hit_position_to_text_coord (t_game *gdata, double wall_x, double open_ratio);
double take_hit_door_position (t_ray *ray, t_game *gdata);
double prepare_opened_door_params (t_game *gdata, int map_x, int map_y);

/*DOOR_RAYCASTING*/
void door_raycast (t_ray *ray, t_game *gdata, int *check_ray_x_in_map, int *check_ray_y_in_map);
void check_vertical_door(t_ray *ray, t_door door_ray, t_game *gdata, int *check_ray_x_in_map);
void check_horizontal_door(t_ray *ray, t_door door_ray, t_game *gdata, int *check_ray_y_in_map);

/*DOOR_RAYCASTING_UTILS*/
void update_door_horizontal_coords (t_ray *ray, double first_dist_y_tmp, int check_ray_y_in_map_tmp, int line_crossing);
void update_door_vertical_coords (t_ray *ray, double first_dist_x_tmp, int check_ray_x_in_map_tmp, int line_crossing);
void horizontal_coords_convert (t_ray *ray, t_game *gdata);
void vertical_coords_convert (t_ray *ray, t_game *gdata);

/*UPDATE_DOORS_STATUS*/
void update_doors(t_game *gdata);
double get_distance_to_door(t_game *gdata, int door_x, int door_y);

//------------------------------------------------
//					PRINT_MAP
//------------------------------------------------

/*TEXTURES*/
int		prepare_animation (t_game *gdata);
int		prepare_textures (t_game *gdata);
int		load_image(t_game *gdata, t_image *image, char *path);
int		check_file_can_be_open(char *path);

/*PRINT_MAP*/
void 	print_map (t_game *gdata, t_map map);
void	prepare_print_params(t_game *gdata, t_ray *ray, t_map map);
void	print_sky(t_game *gdata, t_ray *ray, int *row, int column);
void	print_floor(t_game *gdata, t_ray *ray, int row, int column);

/*PRINT_WALLS*/
void 	print_texture_walls (t_game *gdata, t_ray *ray, int *row, int *column);
void 	print_wall_column(t_game *gdata, int *row, int *column, t_image *texture);
void 	get_texture_row(t_game *gdata, t_image *texture,  double *tex_start_offset);
void 	get_texture_column(t_image *texture, double *wall_x, int *tex_x);
void 	get_column (t_game *gdata, t_ray *ray, double *wall_x);

/*PRINT_DOORS*/
void print_door (t_game *gdata, t_ray *ray, int *row, int *column);
void print_door_column(t_game *gdata, int *row, int *column, t_image *texture, int tex_x, double tex_start_offset, double door_distance);


/*PRINT_MAP_UTILS*/
int 	get_texture_pixel(t_image *texture, int tex_x, int tex_y);
t_image *get_wall_texture(t_ray *ray, t_game *gdata);
int 	rgb_to_hex(int r, int g, int b);

//------------------------------------------------
//					PRINT_MINIMAP
//------------------------------------------------

/*PRINT_FOV_AND_VISION_ANGLE*/
void    calculate_and_print_fov_and_vision_angle(t_game *gdata);
void 	print_FOV(t_game *gdata, t_vision vision, double x, double y) ;
void 	print_vision_angle(t_game *gdata, double x, double y, t_vision vision);

/*PRINT_MINIMAP_SKELETON*/
void	print_minimap(t_game *gdata);
void 	print_player(t_game *gdata, t_player player, int x, int y);

void	browse_minimap_pixels(t_game *gdata);
void	render_pixel(t_game *gdata, int pixel_x, int pixel_y);
int	is_out_of_bounds(t_game *gdata, int pixel_x, int pixel_y);
int	is_valid_matrix_cell(t_game *gdata, int  matrix_cell_x, int matrix_cell_y);
void	draw_cell_pixel(t_game *gdata, char cell, int pixel_x, int pixel_y);
void	draw_checkerboard_pixel(t_game *gdata, int pixel_x, int pixel_y);


//------------------------------------------------
//					DRAGON
//------------------------------------------------

/*DO_DRAGON_ANIMATION*/
void do_dragon_animation(t_game *gdata);

/*PRINT_DRAGON*/
void	print_dragon(t_game *gdata);

//------------------------------------------------
//					MOVEMENTS
//------------------------------------------------

/*PRESS_OR_RELEASE_KEY*/
void	cursor_rotation(double rotation_speed, t_game *gdata, int flag);
void	cursor_handle(double xpos, double ypos, void *param);
int		there_is_a_key_pressed(t_game *gdata);
void	press_key(mlx_key_data_t keydata, void *param);
void	release_key(mlx_key_data_t keydata, t_game *gdata);

/*MOVE_PLAYER*/
void	move_player(t_game *gdata, t_vision vision, double *target_x, double *target_y);
void	prepare_next_position(t_game *gdata, t_vision vision, double *move_x, double *move_y);

/*CHECK_COLLISION*/
int check_collision_x(t_game *gdata, double target_x);
int check_collision_y(t_game *gdata, double target_y);

/*ROTATE PLAYER*/
void 	rotate_player(t_player *player, t_vision *vision);

//------------------------------------------------
//					RENDER
//------------------------------------------------
void	render_game(void *param);


//-------------------------------------------------
//				FREE/ERRORS
//-------------------------------------------------
void	exit_error(char *msg, int status);
void	msg_error(char *msg, char *msg2);
void	free_matrix(char **matrix);
void	clean_path(t_path *path);
void	clean_data(t_game *gdata);


#endif