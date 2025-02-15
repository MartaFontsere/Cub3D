/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/15 18:55:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/Libft/libft.h"
//# include "sprites.h"
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
# define BLACK 0x000000FF
# define DARK_GREY 0x3C3C3CFF
# define MEDIUM_GREY 0X696969FF
//# define MEDIUM_GREY 0X575757FF
# define SOFT_GREY 0x959595FF
//# define LIGHT_GREY 0XD7D7D7FF
# define RED1 0xFF0000FF
//# define YELLOW1 0xFFFF00FF // el FF final es maxima opacidad
# define YELLOW1 0xFFC006FF
# define SOFT_YELLOW 0xFEF4D3FF
//# define SOFT_YELLOW 0xFAFDC9FF
# define BLUE1 0X9AC4FFFF

/*TEXTURES*/ //LUEGO BORRAR PATHS, PARA MIENTRAS SIN PARSING
#define NORTH_TEXTURE "textures/map_walls/opcion2/Norte.xpm42"
#define SOUTH_TEXTURE "textures/map_walls/opcion2/Sur.xpm42"
#define WEST_TEXTURE "textures/map_walls/opcion2/Oeste.xpm42"
#define EAST_TEXTURE "textures/map_walls/opcion2/Este.xpm42"
//esto no borrar:
#define SKY_TEXTURE "textures/sky/Sky_10.xpm42"
	//opcion1
// #define WIDTH_NORTH_TEXTURE 1500
// #define HEIGHT_NORTH_TEXTURE 994
// #define WIDTH_SOUTH_TEXTURE 360
// #define HEIGHT_SOUTH_TEXTURE 240
// #define WIDTH_WEST_TEXTURE 626
// #define HEIGHT_WEST_TEXTURE 417
// #define WIDTH_EAST_TEXTURE 626
// #define HEIGHT_EAST_TEXTURE 414

	//opcion2
#define WIDTH_NORTH_TEXTURE 1000
#define HEIGHT_NORTH_TEXTURE 1000
#define WIDTH_SOUTH_TEXTURE 1000
#define HEIGHT_SOUTH_TEXTURE 1000
#define WIDTH_WEST_TEXTURE 1000
#define HEIGHT_WEST_TEXTURE 1000
#define WIDTH_EAST_TEXTURE 1000
#define HEIGHT_EAST_TEXTURE 1000

//cielo
// #define WIDTH_SKY_TEXTURE 1920
// #define HEIGHT_SKY_TEXTURE 960
// #define WIDTH_SKY_TEXTURE 1800
// #define HEIGHT_SKY_TEXTURE 1013
// #define WIDTH_SKY_TEXTURE 1408
// #define HEIGHT_SKY_TEXTURE 704
#define WIDTH_SKY_TEXTURE 2816
#define HEIGHT_SKY_TEXTURE 704

/*PLAYER ORIENTATION*/
# define NORTH M_PI_2 //90 grados
# define SOUTH 3 * M_PI_2 // 270 grados
# define EAST 0 //0 grados
# define WEST M_PI //180 grados



/*MOVE*/
# define MOVE_RIGHT 0
# define MOVE_LEFT 1
# define MOVE_UP 2
# define MOVE_DOWN 3

/*PLAYER SPEED*/
# define MOVE_SPEED 3 // cuantos pixeles se mueve cada vez que tocamos una tecla
# define ROTATION_SPEED 0.04

/*MAP*/
#define PX_MAP_WIDTH 2560
#define PX_MAP_HEIGHT 1440
// #define NORTH_WALL_COLOR 0XFF9A9AFF
// #define SOUTH_WALL_COLOR 0XFFD29AFF
// #define EAST_WALL_COLOR 0XFFFF9AFF
// #define WEST_WALL_COLOR 0XFF9AFBFF
// #define SKY_COLOR 0X9AC4FFFF
// #define FLOOR_COLOR 0X588650FF
// #define FLOOR_COLOR0XA3FF9AFF

//BORRAR, ESTARA EN EL PARSING
#define CEELING_R 154
#define CEELING_G 196
#define CEELING_B 255
#define FLOOR_R 88
#define FLOOR_G 134
#define FLOOR_B 80

/*MINIMAP*/
#define PX_MINIMAP_WIDTH 520
#define PX_MINIMAP_HEIGHT 340




//DEFINIR TAMAÑO DE VENTANA DE LAS CASILLAS CORRESPONDIENTES * 64 PIXELES (encontrar el mapa maximo)
//ALTURA DEL PLAYER DE 32 PIXELES
//PROJECTION PLANE DE 320 DE ANCHO Y 200 DE ALTO
/*
Dimension of the Projection Plane = 320 x 200 units
Center of the Projection Plane = (160,100)
Distance to the Projection Plane = 277 units
Angle between subsequent rays = 60/320 degrees*/

typedef struct s_color
{
	int					R;
	int					G;
	int					B;
	char				**split;
	struct s_path		*shader;
}						t_color;

typedef struct s_path
{
    char		*NO;//Path textura cara norte
	char		*SO;//Path textura cara sur
	char		*WE;//Path textura cara oeste
	char		*EA;//Path textura cara este
	int			p_count;
	int			c_count;
	int			err_flag;
	t_color		C; //Estructura con el color en RGB
	t_color		F; //Estructura con el color en RGB
}				t_path;

typedef struct s_image
{
	xpm_t		*xpm;
	mlx_image_t	*data;
}				t_image;

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
} 				t_texture;

typedef struct s_mlx
{
	mlx_t		*init;
	int			window_height;
	int			window_width;
	mlx_image_t	*image;
	mlx_image_t	*mini_image;

}				t_mlx;


typedef struct s_ray 
{
    double current_angle;
    double dir_x;       // Dirección X del rayo
    double dir_y;       // Dirección Y del rayo
    double first_dist_x; // distancia desde la posición actual del player hasta la primera línea vertical de la celda de la cuadrícula
    double first_dist_y; // // distancia desde la posición actual del player hasta la primera línea horizontal de la celda de la cuadrícula
   	//Resumen: Distancia desde el inicio del rayo hasta la primera línea de la cuadrícula en cada dirección (X o Y).
    double other_dist_x; // Cuánto hay que moverse en X para pasar a la siguiente línea vertical de la celda de la cuadrícula. 
    double other_dist_y; //Cuánto hay que moverse en Y para pasar a la siguiente línea horizontal de la celda de la cuadrícula.
    // Resumen: Distancia constante entre cada cruce de líneas en la cuadrícula, después del primer encuentro. Despues del primer cruce, el resto de cruces son constantes.  
    int x_sign;
    int y_sign; // Indican si el rayo se mueve hacia adelante o atrás en cada eje.
    //Ej: Si el rayo va a la izquierda (dir_x < 0), x_sign = -1. Si el rayo va a la derecha (dir_x > 0), x_sign = 1.
    int line_crossing; //0 = choque en X, 1 = choque en Y (para texturas)// nos dice qué cara de una celda fue atravesada por el rayo en su último avance. Indica si el rayo choca contra una pared vertical (side = 0, osea se movió en X) o una horizontal (side = 1, osea se movió en Y). indica con qué tipo de línea de la celda el rayo acaba de chocar. No indica si chocó con una pared del mapa, sino si cruzó una línea vertical u horizontal dentro de la cuadrícula.


    double cell_collision_x; // Punto de colisión en X (en casillas)
    double cell_collision_y; // Punto de colisión en Y (en casillas)
    double px_collision_x; // Punto de colisión en X (en pixeles)
    double px_collision_y; // Punto de colisión en Y (en pixeles)
   	
   	double diagonal_distance;    // El largo del rayo. Distancia del origen del rayo a la pared en casillas (para 3D)
   	double perpendicular_distance;
}			t_ray;


// Estructura para el campo de visión (FOV)
typedef struct s_fov {
    int     num_rays;        // Número de rayos (ej: ancho de la ventana)
    double  fov_rad;      // Campo de visión en radianes (ej: 1.0472 ≈ 60°)
    t_ray   *rays;           // Puntero al array de rayos (uno por columna de pantalla)
} t_fov;

//RAYS SOLO TIENE QUE SER PUNTERO, PORQUE ES DE TIPO ESTRUCTURA CON MAS COSAS DENTRO, SINO SERIA MATRIZ, PARA METER COSAS EN CADA PUNTERO, NO?


typedef struct s_vision 	
{
	double		vision_angle; // Orientacion Inicial en grados de la vision del personaje
	double 		last_vision_angle;
	t_fov    	FOV;            // Datos del FOV y rayos

} 				t_vision;



typedef struct s_player
{
	int			raw_x; // Posición Inicial del Personaje en X (en casillas)
	int			raw_y; // Posición Inicial del Personaje en Y (en casillas)
	double		x; // Posición Inicial del Personaje centrado en la casilla en X (en pixeles para minimapa)
	double		y; // Posición Inicial del Personaje centrado en la casilla en Y (en pixeles para minimapa)
	// double 	midle_x; // Posición del Personaje centrado en la casilla en X (en pixeles para minimapa)
	// double 	midle_y; // Posición del Personaje centrado en la casilla en Y (en pixeles para minimapa)
	double  	radius; // radio del circulo que representara el personaje
	int  		mov_right;
	int  		mov_left;
	int  		mov_up;
	int 		mov_down;
	int  		rotate_right;
	int 		rotate_left;

}				t_player;

typedef struct s_minimap
{
	//mlx_image_t		*background_img;
	int				px_width; // Valor máximo X del minimapa (en pixels)
	int				px_height; // Valor máximo Y del minimapa (en pixels)
	double 			px_in_cell_width; // Cantidad de pixels por cada celda en el eje X
	double 			px_in_cell_height; //Cantidad de pixels por cada celda en el eje Y
}					t_minimap;

typedef struct s_map
{
//	char			*north;
//	char			*south;
//	char			*west;
//	char			*east;
	// char			*raw_floor;
	// char			*raw_ceiling;
	// uint32_t		floor;
	// uint32_t		ceiling;
	char			*rawmap; // Mapa sin procesar
	char			**matrix; // Mapa en matriz
	int				px_width; // Valor máximo X del mapa (en pixels)
	int				px_height; // Valor máximo Y del mapa (en pixels)
	int				cells_width; // Valor máximo X del mapa (en casillas)
	int				cells_height; // Valor máximo Y del mapa (en casillas)
}					t_map;


typedef struct s_game
{
	t_texture 		texture;
	t_player		player;
	t_map			map;
	t_minimap 		minimap;
	t_vision 		vision;

	t_mlx			mlx; // ???en funcion de que hacerlo puntero o no?
	int 			finish_game;
}					t_game;

//??? En base a que decidir si las variables las creas como puntero o la variable en si. Como actua en las llamadas mandarme gdata como puntero y lo de dentro que sean variables, se cambia igual el valor no? NO tengo que mandar como puntero la segunda estructura ej (player, para cambiar x). 
//Como inicializar en funcion de si es puntero o variable, yo inicializo el contenido final, no el container de la estructura en si, no?

//MAIN
void	close_window(t_game	*gdata);

//INITIALITATIONS
void	init_gdata_values(t_game *gdata);
void	init_minimap(t_game *gdata, t_map *map);
void 	init_player_parameters (t_game *gdata, t_player *player);
void	init_player_position(t_game *gdata, t_map *map_info, t_player *player);
void	init_player_orientation(t_map *map, t_vision *vision);
int init_vision_parameters (t_game *gdata, t_vision *vision);
int		init_mlx(t_mlx *mlx);
int	create_new_images(t_game *gdata, t_mlx *mlx);
void init_texture_params (t_texture *texture);
void init_map (t_map *map);

//PSEUDOPARSING
char **parsing_pre_yahaira(t_game *gdata);

//PRINT MAP
int	prepare_textures (t_game *gdata);
void print_map (t_game *gdata, t_mlx mlx, t_map map);

//PRINT MINIMAP
void	print_minimap(t_game *gdata);

void print_empty_space (t_mlx mlx, t_minimap minimap, t_map map);
void print_walls (t_mlx mlx, t_minimap minimap, t_map map);
void print_background (t_mlx mlx, t_minimap minimap);
void	print_player_and_fov(t_game *gdata);

//PRINT PLAYER PARAMS
void print_player (t_game *gdata, t_player player, double x, double y, int color);
void print_vision_angle(t_game *gdata, double x, double y, double vision_angle, int color);
void print_FOV(t_game *gdata, t_vision vision, double x, double y, double vision_angle, int color);

//RENDER
void render_game (void *param);

//MOVE
void	prepare_movement(t_game *gdata, t_vision vision, double *target_x, double *target_y);
void rotate_player(t_player *player, t_vision *vision);
void calculate_fov(t_game *gdata, double x, double y);
void print_player_FOV_in_motion(t_game *gdata, t_player player, double target_x, double target_y);
void	print_player_move(t_game *gdata, t_player player, double target_x, double target_y);
void print_player_view_in_motion (t_game *gdata, t_player player, double target_x, double target_y);

//PRESS KEY
int	there_is_a_key_pressed(t_game *gdata);
void	press_key(mlx_key_data_t keydata, void *param);
void	set_mov_params(t_game *gdata, int *move_direction);
void	reset_mov_params(t_game *gdata);
void	release_key(mlx_key_data_t keydata, t_game *gdata);

//COLLISIONS
int	check_collision(t_game *gdata, double target_x, double target_y);

//ERROR
void	write_error(const char *str);

#endif