/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 16:44:29 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "../libs/Libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

/*COLORS*/
# define END "\x1b[0m"
# define RED "\e[1;91m"
# define YELLOW "\e[1;93m"
# define BLUE "\e[1;94m"
# define GREEN "\e[1;92m"
# define CYAN "\e[1;96m"
# define PURPLE "\e[1;95m"
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

/*MINIMAP*/
#define MINIMAP_PX_WIDTH 515
#define MINIMAP_PX_HEIGHT 340
#define MINIMAP_PX_CELL_WIDTH 24
#define MINIMAP_PX_CELL_HEIGHT 24

#define DOOR_START_OPEN_DISTANCE 2.2 // distancia en casillas
#define DOOR_END_OPEN_DISTANCE 1.4


typedef struct s_path	t_path;
typedef struct s_image
{
	xpm_t		*xpm;
	mlx_image_t	*data;
}				t_image;

typedef struct s_color
{
	int			R;
	int			G;
	int			B;
	char		**split;
	int			assigned;
	int			is_path;//decimos que C || F tienen path en lugar del RGB
	char		*color_path;//guardamos el path de la textura
	t_path		*path;
}				t_color;

struct s_path
{
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*tmp_str;
	int			p_count;
	int			c_count;
	int			err_flag;
	t_color		C;
	t_color		F;
};

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

typedef struct s_miniprint
{
	int	start_x;
	int	start_y;

} t_miniprint;

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
	int			cursor_on;//AQUI CURSOR
	double		new_xpos;//AQUI CURSOR
	double		last_xpos;//AQUI CURSOR
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
	char		**matrix;
	char		**tmp_matrix;
	char		**void_matrix;
	char		*fd_path;
	char		pos;
	int			is_map;
	size_t		c_width;
	size_t		c_height;
	int			px_width; // Valor máximo X del mapa (en pixels)
	int			px_height; // Valor máximo Y del mapa (en pixels)
	int			j;
	int			init;
	int			open;
	//t_path		path;
}				t_map;
typedef struct s_game
{
	t_texture 		texture;
	t_player		player;
	t_map			map;
	t_minimap 		minimap;
	t_vision 		vision;
	t_collision 	collision;
	t_print 		print_map;
	t_miniprint		print_minimap;
	t_mlx			mlx; 
	int 			finish_game;
}					t_game;

void	print_dirs(char **matrix, int i, int j, int end);//DEL
void	cursor_handel(double ypos, double xpos, void *param);
void	cursor_rotation(double rotation_speed, t_game *gdata, int flag);
//-------------------------------------------------

//					MAIN
//-------------------------------------------------
void	init_map_params(t_game *gdata, t_map *map);
void	init_textures_and_colors_path(t_texture *texture, t_path *path);

//-------------------------------------------------
//				FREE/ERRORS
//-------------------------------------------------
void	exit_error(char *msg, int status);
void	free_matrix(char **matrix);
void	clean_path(t_path *path);
void	clean_data(t_game *gdata);
void	free_map_sprites(t_game *gdata, t_texture *texture);
/*msg error*/
void	msg_error(char *msg, char *msg2);

//-------------------------------------------------
//					READ_FD
//-------------------------------------------------
int		create_matrix(char *line, t_map *map);
void	assign_path(char *line, t_path *path, int i);
int		check_line(char *line, t_path *path, t_map *map, int i);
int		fd_is_correct(t_game *gdata, t_map *map);
int		read_file(int ac, char **av, t_game *gdata,t_map *map);

//------------------------------------------------
//					READ_FD_UTILS
//------------------------------------------------
int		check_name(char *map_path);
char	*cpy_path(char *line, t_path *path, int pos, int i);
int		curr_char(int cur, char *line, t_path *path);
int		ft_max_size(char *line, int max);
void	map_control(char *line, t_map *map, t_path *path, int i);

//------------------------------------------------
//					READ_COLORS
//------------------------------------------------
void	get_colors(char *line, t_path *path, int i, char c);
void	get_color_path(char *line, t_color *color, int i);
void	control_c_values(char *line, t_path *path, int init_val, char c);
void	control_f_values(char *line, t_path *path, int init_val, char c);
void	assign_color(char *line, t_path *path, int i);

	//UTILS READ
void	cpy_colors(char *rgb, t_color *color, int i);
char	*clean_str(char *src, int start, int end, t_path *path);
//------------------------------------------------
//						GET_MAP
//------------------------------------------------
char	*cub_strdup(char *s1, int len);
char	**copy_map(char **map, int height);
int		mix_matrix(char **src, t_map *map);
char	*fill_void(t_map *map);
int		get_final_map(char **src, t_map *map);

//------------------------------------------------
//					PARSE_MAP
//------------------------------------------------
int		check_borders(char **matrix, int i, t_map *map);
int		is_close(char **matrix, t_map *map);
int		min_chars(char **map, int i);
int		parse_map(t_game *gdata, char **matrix, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS
//------------------------------------------------
void	check_n_line(char **src, t_map *map);
int		check_esp(size_t i, size_t j, t_map *map);
int		check_zero(size_t i, size_t j, t_map *map);
int		check_player(size_t i, size_t j, t_map *map);

//------------------------------------------------
//					PARSE_MAP_UTILS2
//------------------------------------------------
int		is_door(size_t i, size_t j, t_map *map);
int		check_y_pos(int i, int j, t_map *map);
int		check_x_pos(int i, int j, t_map *map);

#endif