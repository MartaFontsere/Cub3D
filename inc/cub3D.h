/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:53:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/get_next_line/get_next_line.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

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
# define MOVE_SPEED 4
# define ROTATION_SPEED 0.06

/*MAP*/
#define MAP_PX_WIDTH 2560
#define MAP_PX_HEIGHT 1440

/*MINIMAP*/
#define MINIMAP_PX_WIDTH 515
#define MINIMAP_PX_HEIGHT 340
#define MINIMAP_PX_CELL_WIDTH 24
#define MINIMAP_PX_CELL_HEIGHT 24

typedef struct s_image
{
	xpm_t		*xpm;
	mlx_image_t	*data;
}				t_image;

typedef struct s_color
{
	int					R;
	int					G;
	int					B;
	char				**split;
	int					assigned;
	struct s_path		*path;
}						t_color;

typedef struct s_path
{
    char		*NO;//Path textura cara norte
	char		*SO;//Path textura cara sur
	char		*WE;//Path textura cara oeste
	char		*EA;//Path textura cara este
	char		*tmp_str; //DEFINIR
	int			p_count;  //DEFINIR
	int			c_count; //DEFINIR
	int			err_flag; //DEFINIR
	t_color		C; //Estructura con el color en RGB
	t_color		F; //Estructura con el color en RGB
}				t_path;

typedef struct s_texture 
{
	t_path 		path;
	t_image 	north_wall_img;
	t_image 	south_wall_img;
	t_image 	west_wall_img;
	t_image 	east_wall_img;
	int 		C_hex_color;
	int 		F_hex_color;
} 				t_texture;

typedef struct s_print
{
	double 		wall_height;
	double 		draw_wall_start;
	int 		draw_wall_end;
	int 		color;
	int 		tex_x;
    double 		tex_start_offset;
} t_print;

typedef struct s_mlx
{
	mlx_t		*init;
	int			window_height;
	int			window_width;
	mlx_image_t	*image;
}				t_mlx;



typedef struct s_ray 
{
    double 		current_angle;
    double 		dir_x;
    double 		dir_y;
    double 		first_dist_x; 
    double 		first_dist_y; 
    double 		other_dist_x;
    double 		other_dist_y;
    int 		check_ray_x_in_map;
    int 		check_ray_y_in_map;
    int 		x_sign;
    int 		y_sign; 
    int 		line_crossing;
    int 		cell_collision_x;
    int 		cell_collision_y;
    double 		px_collision_x;
    double 		px_collision_y;
   	double 		diagonal_distance;
   	double 		perpendicular_distance;
}				t_ray;

typedef struct s_fov 
{
    int     	num_rays;
    double 	 	fov_rad;
    t_ray   	*rays;
}			 	t_fov;


typedef struct s_vision 	
{
	double		vision_angle;
	t_fov    	FOV;
    double 		projection_factor;
    double 		camera_height_scale;
} 				t_vision;


typedef struct s_collision
{
	double	player_contour_x;
	double	player_contour_y;
	double	angle;
	double	angle_step;
} t_collision;


typedef struct s_player
{
	int 		height;
	int			raw_x;
	int			raw_y;
	double		x;
	double		y;
	double 		cell_player_x;
    double 		cell_player_y;
	double  	radius;
	int  		mov_right;
	int  		mov_left;
	int  		mov_up;
	int 		mov_down;
	int  		rotate_right;
	int 		rotate_left;
	char 		orientation;

}				t_player;

typedef struct s_minimap
{
	int 			c_width;
	int 			c_height;
	int				px_width;
	int				px_height;
	int 			px_in_cell_width;
	int 			px_in_cell_height;
	int 			center_x;
	int 			center_y;

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
	t_texture 		texture;
	t_player		player;
	t_map			map;
	t_minimap 		minimap;
	t_vision 		vision;
	t_collision 	collision;
	t_print 		print_map;
	t_mlx			mlx; 
	int 			finish_game;
}					t_game;


//void update_doors(t_game *gdata);


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
char	*cpy_path(char *line, t_path *path, int pos);
int		curr_char(int cur, char *line, t_path *path);
int 	ft_max_size(char *line, int max);
void	map_control(char *line, t_map *map, t_path *path);

/*READ_FD-UTILS2*/
char	*clean_str(char *src, int end, t_path *path);

/*READ_COLORS*/
void	cpy_colors(char *rgb, t_color *color, int i);
void	get_colors(char *line, t_path *path, int i, int init);
void	assign_color(char *line, t_path *t_path, int i);

/*GET_MAP*/
char	*cub_strdup(char *s1, int len);
char	**copy_map(char **map, int height);
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);

//------------------------------------------------
//					PARSE
//------------------------------------------------

/*PARSE_MAP*/
int		parse_map(t_game	*gdata, char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		is_close(char **matrix, t_map *map);
int		check_borders(char **matrix, int i, t_map *map);

/*PARSE_UTILS*/
void	check_n_line(char **src, t_map *map);
int		check_esp(int x, int y, t_map *map);
int		check_zero(int x, int y, t_map *map);
int		check_player(int x, int y, t_map *map);

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

/*INIT_PRINT_PARAMS*/
void	init_textures_and_colors_path(t_texture *texture, t_path *path);

/*INIT_MLX_PARAMS*/
int		init_mlx(t_game *gdata, t_mlx *mlx);
int		create_new_images(t_game *gdata, t_mlx *mlx);
int		put_image_to_window(t_game *gdata, t_mlx *mlx);

//------------------------------------------------
//					RAYCASTING
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


//------------------------------------------------
//					PRINT_MAP
//------------------------------------------------

/*TEXTURES*/
int		prepare_animation (t_game *gdata);
int		prepare_textures (t_game *gdata);
int		load_image(t_game *gdata, t_image *image, char *path);
int		check_file_can_be_open(char *path);

/*PRINT_MAP*/
void 	print_map (t_game *gdata, t_mlx mlx, t_map map);
void	prepare_print_params(t_game *gdata, t_ray *ray, t_map map);
void	print_sky(t_game *gdata, t_mlx mlx, int *row, int *column);
void	print_floor(t_game *gdata, t_mlx mlx, int *row, int *column);

/*PRINT_WALLS*/
void 	print_texture_walls (t_game *gdata, t_ray *ray, int *row, int *column);
void 	print_wall_column(t_game *gdata, int *row, int *column, t_image *texture);
void 	get_texture_row(t_game *gdata, t_image *texture,  double *tex_start_offset);
void 	get_texture_column(t_image *texture, double *wall_x, int *tex_x);
void 	get_wall_column (t_game *gdata, t_ray *ray, double *wall_x);

/*PRINT_UTILS*/
int 	get_texture_pixel(t_image *texture, int tex_x, int tex_y);
t_image *get_wall_texture(t_ray *ray, t_game *gdata);
int 	rgb_to_hex(int r, int g, int b);

//------------------------------------------------
//					MOVEMENTS
//------------------------------------------------

/*PRESS_OR_RELEASE_KEY*/
int		there_is_a_key_pressed(t_game *gdata);
void	press_key(mlx_key_data_t keydata, void *param);
void	release_key(mlx_key_data_t keydata, t_game *gdata);

/*MOVE_PLAYER*/
void	move_player(t_game *gdata, t_vision vision, double *target_x, double *target_y);
void	prepare_next_position(t_game *gdata, t_vision vision, double *move_x, double *move_y);

/*CHECK_COLLISION*/
int		check_collision(t_game *gdata, double target_x, double target_y);

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