/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/21 13:39:57 by yanaranj         ###   ########.fr       */
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

			/*TEXTURES*/ //LUEGO BORRAR PATHS, PARA MIENTRAS SIN PARSING
			#define NORTH_TEXTURE "textures/map_walls/opcion2/Norte.xpm42"
			#define SOUTH_TEXTURE "textures/map_walls/opcion2/Sur.xpm42"
			#define WEST_TEXTURE "textures/map_walls/opcion2/Oeste.xpm42"
			#define EAST_TEXTURE "textures/map_walls/opcion2/Este.xpm42"

			//esto no borrar:
			// #define SKY_TEXTURE "textures/sky/Sky_10.xpm42"
			#define SKY_TEXTURE "textures/sky/Sky_32.xpm42"
			#define FLOOR_TEXTURE "textures/floor/Floor_4.xpm42"
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
	int 		C_hex_color; // Color transformado a hexadecimal
	int 		F_hex_color; // Color transformado a hexadecimal

	//BONUS
	t_image 	sky_img;
	t_image 	floor_img;
	t_image  	door_img;
	t_image 	dragon_img[4];
} 				t_texture;

typedef struct s_print
{
	double 		wall_height;
	double 		draw_wall_start;
	int 		draw_wall_end;
	double 		door_height;
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
	mlx_image_t	*mini_image;

}				t_mlx;

typedef struct s_door
{
	int line_crossing_tmp;
	int  check_ray_x_in_map_tmp;
	int  check_ray_y_in_map_tmp;
	double first_dist_x_tmp;
	double first_dist_y_tmp;
}		t_door;


typedef struct s_ray 
{
    double 		current_angle;
    double 		dir_x;       // Dirección X del rayo
    double 		dir_y;       // Dirección Y del rayo

    //Wall
    double 		first_dist_x; // distancia desde la posición actual del player hasta la primera línea vertical de la celda de la cuadrícula
    double 		first_dist_y; // // distancia desde la posición actual del player hasta la primera línea horizontal de la celda de la cuadrícula
   			//Resumen: Distancia desde el inicio del rayo hasta la primera línea de la cuadrícula en cada dirección (X o Y).
    double 		other_dist_x; // Cuánto  hay que moverse en X para pasar a la siguiente línea vertical de la celda de la cuadrícula. 
    double 		other_dist_y; //Cuánto hay que moverse en Y para pasar a la siguiente línea horizontal de la celda de la cuadrícula.
   			 // Resumen: Distancia constante entre cada cruce de líneas en la cuadrícula, después del primer encuentro. Despues del primer cruce, el resto de cruces son constantes.  
    int 		check_ray_x_in_map; // Representa la celda en la cuadrícula donde está el rayo(índices de la matriz del mapa). Empieza en la casilla del player
    int 		check_ray_y_in_map; // Representa la celda en la cuadrícula donde está el rayo  (índices de la matriz del mapa). Empieza en la casilla del player
    int 		x_sign; // Indican si el rayo se mueve hacia adelante o atrás en cada eje.
    int 		y_sign; 
   			 //Ej: Si el rayo va a la izquierda (dir_x < 0), x_sign = -1. Si el rayo va a la derecha (dir_x > 0), x_sign = 1.
    int 		line_crossing; //0 = choque en X, 1 = choque en Y (para texturas)// nos dice qué cara de una celda fue atravesada por el rayo en su último avance. Indica si el rayo choca contra una pared vertical (side = 0, osea se movió en X) o una horizontal (side = 1, osea se movió en Y). indica con qué tipo de línea de la celda el rayo acaba de chocar. No indica si chocó con una pared del mapa, sino si cruzó una línea vertical u horizontal dentro de la cuadrícula.

    int 		cell_collision_x; // Punto de colisión en X (en casillas)
    int 		cell_collision_y; // Punto de colisión en Y (en casillas)
    double 		px_collision_x; // Punto de colisión en X (en pixeles)
    double 		px_collision_y; // Punto de colisión en Y (en pixeles)
   	
   	double 		diagonal_distance;    // El largo del rayo. Distancia del origen del rayo a la pared en casillas (para 3D)
   	double 		perpendicular_distance;
//Door
   	int hit_door;              // Flag que indica si el rayo tocó una puerta cerrada
   	t_door 		door_ray;

   	//Floor
   	double 		pixel_distance_to_floor; // distancia del player al pixel de suelo que queremos dibujar en casillas
	// double floor_x; //posicion del pixel en x
	// double floor_y; //posicion del pixel en y

}				t_ray;


// Estructura para el campo de visión (FOV)
typedef struct s_fov 
{
    int     	num_rays;        // Número de rayos (ej: ancho de la ventana)
    double 	 	fov_rad;      // Campo de visión en radianes (ej: 1.0472 ≈ 60°)
    t_ray   	*rays;           // Puntero al array de rayos (uno por columna de pantalla)
}			 	t_fov;



typedef struct s_vision 	
{
	double		vision_angle; // Orientacion Inicial en grados de la vision del personaje
	t_fov    	FOV;            // Datos del FOV y rayos
    double 		projection_factor; // Es como un factor de escala que convierte distancias del mundo 2D (minimapa) en una altura en la pantalla (3D), , asegurando que los objetos más lejanos sean más pequeños y los cercanos sean más grandes.
    double 		camera_height_scale; // Es una constante que se deriva de la altura de la cámara o jugador. Se trata de un valor utilizado para la proyección del mundo 3D sobre la pantalla 2D. Se utiliza como un factor de escala para ajustar las dimensiones en la proyección según la altura del jugador. 

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
	int 		height; // Altura del player en el mundo 3D
	int			raw_x; // Posición Inicial del Personaje en X (en casillas)
	int			raw_y; // Posición Inicial del Personaje en Y (en casillas)
	double		x; // Posición Inicial del Personaje centrado en la casilla en X (en pixeles para minimapa). A cada movimiento se ira actualizando
	double		y; // Posición Inicial del Personaje centrado en la casilla en Y (en pixeles para minimapa). A cada movimiento se ira actualizando
	double 		cell_player_x; //posición en casillas del player
    double 		cell_player_y; //posición en casillas del player
	double  	radius; // radio del circulo que representara el personaje
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
	int 			c_width; // Número de casillas que caben en el eje X dentro de la ventana del minimapa
	int 			c_height; // Número de casillas que caben en el eje Y dentro de la ventana del minimapa
	int				px_width; // Valor máximo X del minimapa (en pixels)
	int				px_height; // Valor máximo Y del minimapa (en pixels)
	int 			px_in_cell_width; // Cantidad de pixels por cada celda en el eje X
	int 			px_in_cell_height; //Cantidad de pixels por cada celda en el eje Y
	int 			center_x; //casilla central del minimapa en el eje X
	int 			center_y; //casilla central del minimapa en el eje Y

}					t_minimap;


typedef struct s_map
{

	char			**matrix; // Mapa en matriz
	char			**tmp_matrix; //DEFINIR
	char			**void_matrix; //DEFINIR
	char			*fd_path; //DEFINIR
	int				is_map; //DEFINIR
	int				j; //DEFINIR
	int				init; //DEFINIR
	int				open; //DEFINIR

	int				px_width; // Valor máximo X del mapa (en pixels)
	int				px_height; // Valor máximo Y del mapa (en pixels)
	int				c_width; // Valor máximo X del mapa (en casillas)
	int				c_height; // Valor máximo Y del mapa (en casillas)
	
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


void	print_dirs(char **matrix, int i, int j, int end);//DEL

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
int parse_map(char **matrix, t_map *map,t_game *gdata);
int		min_chars(char **map, int i);
int		is_close(char **matrix, t_map *map, t_game *gdata);
int		check_borders(char **matrix, int i, t_map *map);

/*PARSE_DOOR*/
int	is_door(int i, int j, t_map *map, t_game *gdata);
int	check_x_pos(int i, int j, t_map *map, t_game *gdata);
int	check_y_pos(int i, int j, t_map *map, t_game *gdata);

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
// void 	prepare_vertical_final_collision_params (t_ray *ray, t_game *gdata, double x);
// void 	prepare_horizontal_final_collision_params (t_ray *ray, t_game *gdata, double y);
void 	prepare_vertical_collision_params (t_ray *ray, t_game *gdata, double x);
void 	prepare_horizontal_collision_params (t_ray *ray, t_game *gdata, double y);
void 	controll_x_limit_case (t_ray *ray, int check_ray_x_in_map, double cell_player_x);
void 	controll_y_limit_case (t_ray *ray, int check_ray_y_in_map, double cell_player_y);
double 	compute_collision_coordinate(int check_ray_coord, int ray_sign, double px_in_cell_size);



void check_matrix_lines (t_ray *ray, int *check_ray_x_in_map, int *check_ray_y_in_map);


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
//					PRINT_MINIMAP
//------------------------------------------------

/*PRINT_FOV_AND_VISION_ANGLE*/
void    calculate_and_print_fov_and_vision_angle(t_game *gdata);
void 	print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color) ;
void 	print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color);

/*PRINT_MINIMAP_SKELETON*/
void	print_minimap(t_game *gdata);
void 	print_player(t_game *gdata, t_player player, int x, int y);

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
int		there_is_a_key_pressed(t_game *gdata);
void	press_key(mlx_key_data_t keydata, void *param);
void	release_key(mlx_key_data_t keydata, t_game *gdata);

/*MOVE_PLAYER*/
void	move_player(t_game *gdata, t_vision vision, double *target_x, double *target_y);
void	prepare_next_position(t_game *gdata, t_vision vision, double *move_x, double *move_y);

/*CHECK_COLLISION*/
// int		check_collision(t_game *gdata, double target_x, double target_y);
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