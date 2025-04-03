/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:02:13 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/03 12:07:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

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
	int					is_path;
	char				*color_path;
	struct s_path		*path;
}						t_color;

typedef struct s_path
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


typedef struct s_draw_ray
{
    double current_x;
    double current_y;
    double x_distance;
    double y_distance;
    double x_inc;
    double y_inc;
    double steps;
} t_draw_ray;


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
//Print
   	t_draw_ray 	draw;

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


typedef struct s_draw_va
{
	double origin_x;
	double origin_y;
	int offset_x;
	int offset_y;
	int pixel_x;
	int pixel_y;

    
} t_draw_va;


typedef struct s_vision 	
{
	double		vision_angle; // Orientacion Inicial en grados de la vision del personaje
	t_draw_va  draw_vision_angle;
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
	char			**matrix;
	char			**tmp_matrix;
	char			**void_matrix;
	char			*fd_path;
	int				is_map;
	int				j;
	int				init;
	int				open;
	char			pos;
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
	t_miniprint		print_minimap;
	t_mlx			mlx; 
	int 			finish_game;
}					t_game;

#endif