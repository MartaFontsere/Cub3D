/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:55:35 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/13 22:57:39 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



int rgb_to_hex(int r, int g, int b)
{
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;  // 0xFF para la opacidad (canal alfa)
}

/*
🔹 (r << 24): Mueve el valor de rojo 24 bits a la izquierda para que ocupe los 8 bits mas a la izquierda.
🔹 (g << 16): Mueve el valor de verde 16 bits a la izquierda para que ocupe los siguientes 8 bits.
🔹 (b << 8): Mueve el valor de azul 8 bits a la izquierda.
🔹 | 0xFF: Agrega 0xFF (255 en decimal) al final, lo que establece el canal alfa (opacidad) en 100% (completamente visible).

Cuando guardamos los valores en RGB, estos siguen siendo enteros normales en base decimal.
Lo que realmente ocurre es que cuando los combinas con desplazamiento de bits (<<) y operaciones OR (|), el resultado se almacena en una variable entera de 32 bits

Internamente, siguen siendo números enteros.
El formato hexadecimal solo se usa cuando imprimes el número con %X o %x en printf.
En código, los números son solo números. La forma en que los ves depende de cómo los imprimas.


Explicación:
El operador | se usa para combinar los valores de los colores (R, G, B, A) en un solo número de 32 bits.
r << 24 → Desplaza r 24 bits a la izquierda.
g << 16 → Desplaza g 16 bits a la izquierda.
b << 8 → Desplaza b 8 bits a la izquierda.
0xFF → Añade 255 (11111111) como canal alfa.

Ejemplo con rgb_to_hex(88, 134, 80):

   (88 << 24)  = 0x58000000
   (134 << 16) = 0x00860000
   (80 << 8)   = 0x00005000
   (0xFF)      = 0x000000FF
---------------------------------
Resultado:      0x588650FF
🔹 Se combinan los valores en un solo número hexadecimal de 32 bits.

El 255 (0xFF en hexadecimal) es el máximo porque un byte (8 bits) puede representar valores del 0 al 255
11111111 en binario es 255 en decimal → es el mayor número posible en 8 bits.

*/


t_image *get_wall_texture(t_ray *ray, t_game *gdata)
{
    if (ray->line_crossing == 1)  // Pared horizontal (Norte o Sur)
    {
        if (ray->y_sign == 1)
            return &gdata->texture.south_wall_img;  // Sur
        else
            return &gdata->texture.north_wall_img;  // Norte
    }
    else  // Pared vertical (Este u Oeste)
    {
        if (ray->x_sign == 1)
            return &gdata->texture.east_wall_img;  // Este
        else
            return &gdata->texture.west_wall_img;  // Oeste
    }
}

int get_texture_pixel(t_image *texture, int tex_x, int tex_y)
{
	// Verificar si las coordenadas están fuera de los límites
    if (tex_x < 0 || (uint32_t)tex_x >= texture->xpm->texture.width ||
        tex_y < 0 || (uint32_t)tex_y >= texture->xpm->texture.height)
        return 0x000000;  // Negro si está fuera de los límites

    // Calcular el índice del píxel en la textura
    int index = (tex_y * texture->xpm->texture.width + tex_x) * 4;  // 4 bytes por píxel (RGBA)
    uint8_t *pixel = &texture->xpm->texture.pixels[index];

    // Obtener el color del píxel
    int color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];
    return color;
}



//VERSION 3. TEXTURAS EN PAREDES Y CIELO, COLOR EN SUELO

//En lugar de pintar un color sólido para el cielo, usarás una textura panorámica del cielo que se desplaza en función de la orientación del jugador.

// Efecto Parallax:

	// Si el jugador gira a la derecha, la textura del cielo se mueve a la izquierda.
	// Si el jugador gira a la izquierda, la textura del cielo se mueve a la derecha.
	// La textura se repite en bucle para dar la ilusión de un cielo infinito.

//🔹 Implementación Paso a Paso
	//Carga una textura de cielo panorámico (como las paredes).
	//Calcula la posición horizontal (tex_x) en la textura según la dirección del jugador.
	//Dibuja el cielo antes de las paredes, usando las coordenadas correctas de la textura.

void print_map (t_game *gdata, t_mlx mlx, t_map map)
{
	// int map.px_width = gdata->mlx.image->width;
    // int map.px_height = gdata->mlx.image->height;

	gdata->texture.C_hex_color = rgb_to_hex(gdata->texture.path.C.R, gdata->texture.path.C.G, gdata->texture.path.C.B);
	gdata->texture.F_hex_color = rgb_to_hex(gdata->texture.path.F.R, gdata->texture.path.F.G, gdata->texture.path.F.B);
 
    int x = 0; 
	while (x < gdata->vision.FOV.num_rays)
    {
    	// Obtener el rayo precalculado
        t_ray *ray = &gdata->vision.FOV.rays[x];

        // Calcular la altura de la pared en píxeles
        double wall_height = map.px_height / ray->perpendicular_distance; // altura total de la pantalla / distancia del jugador a la pared perpendiclarmente (para evitar ojo de pez). A menor distancia, la pared será más alta; a mayor distancia, la pared será más baja
// printf ("map.px_height %d\n", map.px_height);
// printf ("ray->perpendicular_distance %f\n", ray->perpendicular_distance);

         // Calcular los límites verticales de la pared
        int draw_wall_start = (map.px_height / 2) - (wall_height / 2);
        int draw_wall_end = (map.px_height / 2) + (wall_height / 2);

        //Limitar un valor dentro de un rango permitido
        //Si wall_height es muy grande, draw_wall_start podría volverse negativo, y draw_wall_end podría ser mayor que map.px_height, lo que haría que mlx_put_pixel() intentara acceder a píxeles fuera del rango de la imagen, causando el segfault
        //Aseguramos que draw_wall_start nunca sea menor que 0 y que draw_wall_end nunca sea mayor que map.px_height - 1
        if (draw_wall_start < 0) 
        {
        	draw_wall_start = 0;
        }

		if (draw_wall_end >= map.px_height) 
		{
			draw_wall_end = map.px_height - 1;
		}

    // Dibujar el cielo
        // Obtener la textura del cielo
		t_image *sky_texture = &gdata->texture.sky_img;

		// Calcular el desplazamiento del cielo en función de la dirección y la posición del jugador
		double sky_offset_x = (ray->current_angle / (2 * M_PI)) 
		                    + (gdata->player.x * 0.0007);  // Reducir impacto del movimiento lateral

		sky_offset_x -= floor(sky_offset_x);  // Mantener solo la parte decimal

		// Obtener dimensiones de la textura
		int sky_tex_width = sky_texture->xpm->texture.width;
		int sky_tex_height = sky_texture->xpm->texture.height;

		// Calcular posición inicial en la textura
		int tex_x_start = (int)(sky_offset_x * sky_tex_width);

		int y = 0;
		while (y < draw_wall_start)
		{
		    // Aplicar corrección de perspectiva con un pequeño ajuste por el movimiento en Y
		    double screen_y_ratio = (double)(y - (mlx.window_height / 4)) / (mlx.window_height / 4);
		    double vertical_offset = gdata->player.y * 0.0003; // Pequeño desplazamiento en el eje Y
		    int tex_y = (int)((0.5 + screen_y_ratio * 0.5 + vertical_offset) * sky_tex_height);
		    
		    int tex_x = (tex_x_start + x) % sky_tex_width; // Hacer que la textura sea infinita

		    int color = get_texture_pixel(sky_texture, tex_x, tex_y);
		    mlx_put_pixel(mlx.image, x, y, color);
		    y++;
		}
        
// Texturizar la pared
        t_image *texture = get_wall_texture(ray, gdata);  // Obtener la textura correcta segun si el rayo impacta en una pared norte, sur, este u oeste, ya que la textura debe ser diferente.
        
        // Calcular la coordenada horizontal en la textura (tex_x)
        double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
        if (ray->line_crossing == 0)  // Pared vertical
        {
            wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_height;  // Usar la coordenada Y del punto de impacto. Osea miro en que pixel colisiona del eje Y y luego lo divido por el tamaño en pixeles de una casilla en el minimapa (representacion 2d) para saber en que parte de esa casilla esta colisionando. Ej: si colisiona en la casilla 4,75, significa que dentro de la casilla 4 choca en el 75% de esa casilla (entendiendo una casilla como el 100%). Nos quedamos solo con ese 75, porque indica que parte de la textura debemos pintar, me da igual el numero de la casilla
        	//printf ("casilla de colision para textura |%f|\n", wall_x);
        }
        else  // Pared horizontal
        {
            wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;  // Usar la coordenada X del punto de impacto. esa coordenada corresponde a la columna en el eje x de la textura que debera pintarse
        	//printf ("casilla de colision para textura |%f|\n", wall_x);
        }
        
        wall_x = wall_x - floor(wall_x);  // Parte fraccional de la posición dentro de la casilla --> Elimina la parte entera de wall_x y se queda solo con la fracción decimal. Queremos saber dentro de la casilla en qué punto impacta el rayo. Por ejemplo, si wall_x = 4.75, significa que el rayo impactó en la casilla 4, pero dentro de esa casilla impactó en el 75% de su ancho. Nos quedamos solo con 0.75

        //Convertir la coordenada de wall_x en una coordenada en píxeles dentro de la textura --> Las texturas tienen un ancho fijo, por lo que si wall_x = 0.75 y la textura tiene 64 píxeles de ancho, entonces el rayo impactó en el píxel 48 de la textura.
        int tex_x = (int)(wall_x * texture->xpm->texture.width);  // Coordenada horizontal en la textura
        
        // Asegurar que tex_x esté dentro de los límites --> Si tex_x es menor que 0 o mayor que texture->width, intentar acceder a esos valores podría causar un segfault. Esto podria pasar por errores de redondeo y precision, y si pasa como mucho se repetira la primera o la ultima columna de la textura. Cuando estás muy cerca de la pared, el control de tex_x prácticamente nunca será un problema, porque solo estarás viendo una pequeña porción de la textura, y esa porción siempre estará dentro de los límites de la textura
        if (tex_x < 0) 
        	tex_x = 0;
        if ((uint32_t)tex_x >= texture->xpm->texture.width) 
        {
        	tex_x = texture->xpm->texture.width - 1; // (- 1 porque em pieza en 0)
        }

        // Calcular cuánto de la textura debería saltarse si la pared es más grande que la pantalla --> Si la pared proyectada (wall_height) es más alta que la ventana (map.px_height), entonces parte de la textura debería "recortarse" para que solo se muestre el fragmento visible
		double tex_start_offset = 0; // tex_start_offset calcula cuántos píxeles de la textura hay que saltarse para centrar correctamente la imagen en pantalla.
		//Ej: 
			//Supongamos que wall_height = 1200 px y la ventana solo tiene map.px_height = 600 px.
			//Eso significa que 600 píxeles de la pared están fuera de la pantalla (300 arriba y 300 abajo).
			//Hay que empezar la textura en un punto más avanzado para evitar que la parte superior de la textura se muestre en la parte inferior de la pantalla

		if (wall_height > map.px_height)
		{
		    tex_start_offset = ((wall_height - map.px_height) / 2.0) * ((double)texture->xpm->texture.height / wall_height); 
		}
		//Si wall_height es más grande que la pantalla (map.px_height), hay una parte de la textura que no cabe en la pantalla.
		//wall_height - map.px_height calcula cuántos píxeles de más hay--> Si la pared proyectada tiene wall_height = 1200 píxeles, y la pantalla mide map.px_height = 800 píxeles. Esto significa que hay 400 píxeles de la textura que no pueden verse
		//En este caso, no queremos eliminar los 400 píxeles desde el inicio ni desde el final de la textura.
		//Queremos cortar la misma cantidad por arriba y por abajo para que la parte visible de la textura quede centrada en la pantalla.
		//Por eso dividimos entre 2, para repartir la parte que sobra mitad arriba y mitad abajo
				// ((wall_height - map.px_height) / 2.0) --> Calcula cuántos píxeles sobran en total y divide por 2.0 para saber cuánto hay que "cortar" arriba
		//Ahora necesitamos convertir los 200 píxeles en coordenadas de la textura.
			//texture->xpm->texture.height es la altura real de la textura.
			//wall_height es la altura proyectada en la pantalla.
			//(double)texture->xpm->texture.height / wall_height es un factor de escala para convertir los píxeles de la pantalla en píxeles de la textura
				//Ejemplo: Si la textura tiene una altura real de 256 píxeles y la pared proyectada (wall_height) es 1200 píxeles --> (256.0 / 1200) = 0.2133;
				//Ahora multiplicamos este factor por 200 (los píxeles que queremos saltarnos) --> tex_start_offset = 200 * 0.2133 = 42.67 ≈ 43 píxeles.
				//Esto significa que, para centrar la textura, debemos comenzar a dibujarla desde el píxel 43 de la textura real

				// * ((double)texture->xpm->texture.height / wall_height) --> Convierte esa cantidad de píxeles sobrantes a la escala de la textura. texture->xpm->texture.height / wall_height nos da la proporción de la textura que corresponde a un píxel en la pared.

        // Dibujar la pared con textura correctamente alineada
        double tex_y_ratio = (double)texture->xpm->texture.height / wall_height; // tex_y_ratio nos dice cuántos píxeles de la textura corresponden a un píxel en la pantalla. Si wall_height es grande, tex_y_ratio será menor (más detalle de la textura se verá)
        while (y <= draw_wall_end) // Recorrer cada píxel en la pantalla dentro del rango de la pared (draw_wall_start hasta draw_wall_end)  y asignarle el color correcto de la textura.
        {
            // Calcular la coordenada vertical en la textura (tex_y) ajustando el punto de inicio
            int tex_y = (int)((y - draw_wall_start) * tex_y_ratio + tex_start_offset); // Convierte la coordenada de la pantalla y en la coordenada de la textura tex_y. Se usa tex_start_offset para saltar los píxeles invisibles si la pared proyectada es demasiado alta

            // Asegurar que tex_y esté dentro de los límites de la textura (Clamping de tex_y). Evita accesos fuera de los límites de la textura
            if (tex_y < 0) 
            	tex_y = 0;
            if ((uint32_t)tex_y >= texture->xpm->texture.height) 
            	tex_y = texture->xpm->texture.height - 1; // lo ajusta al último píxel válido (- 1 porque em pieza en 0)

            // Obtener el color del píxel de la textura
            int color = get_texture_pixel(texture, tex_x, tex_y);

            // Dibujar el píxel en la pantalla
            mlx_put_pixel(mlx.image, x, y, color);
            y++;
        }

        // Dibujar el suelo
        while (y < map.px_height)
        {
            mlx_put_pixel(mlx.image, x, y, gdata->texture.F_hex_color);
            y++;
        }

        x++;
    }
}





















//VERSION 2, TEXTURAS EN PAREDES Y COLORES EN CIELO Y SUELO
// void print_map (t_game *gdata, t_mlx mlx, t_map map)
// {
// 	// int map.px_width = gdata->mlx.image->width;
//     // int map.px_height = gdata->mlx.image->height;

// 	gdata->texture.C_hex_color = rgb_to_hex(gdata->texture.path.C.R, gdata->texture.path.C.G, gdata->texture.path.C.B);
// 	gdata->texture.F_hex_color = rgb_to_hex(gdata->texture.path.F.R, gdata->texture.path.F.G, gdata->texture.path.F.B);
 
//     int x = 0; 
// 	while (x < gdata->vision.FOV.num_rays)
//     {
//     	// Obtener el rayo precalculado
//         t_ray *ray = &gdata->vision.FOV.rays[x];

//         // Calcular la altura de la pared en píxeles
//         double wall_height = map.px_height / ray->perpendicular_distance; // altura total de la pantalla / distancia del jugador a la pared perpendiclarmente (para evitar ojo de pez). A menor distancia, la pared será más alta; a mayor distancia, la pared será más baja
// // printf ("map.px_height %d\n", map.px_height);
// // printf ("ray->perpendicular_distance %f\n", ray->perpendicular_distance);

//          // Calcular los límites verticales de la pared
//         int draw_wall_start = (map.px_height / 2) - (wall_height / 2);
//         int draw_wall_end = (map.px_height / 2) + (wall_height / 2);

//         //Limitar un valor dentro de un rango permitido
//         //Si wall_height es muy grande, draw_wall_start podría volverse negativo, y draw_wall_end podría ser mayor que map.px_height, lo que haría que mlx_put_pixel() intentara acceder a píxeles fuera del rango de la imagen, causando el segfault
//         //Aseguramos que draw_wall_start nunca sea menor que 0 y que draw_wall_end nunca sea mayor que map.px_height - 1
//         if (draw_wall_start < 0) 
//         {
//         	draw_wall_start = 0;
//         }

// 		if (draw_wall_end >= map.px_height) 
// 		{
// 			draw_wall_end = map.px_height - 1;
// 		}

//         // Dibujar el cielo
//         int y = 0;
//         while (y < draw_wall_start)
//         {
//             mlx_put_pixel(mlx.image, x, y, gdata->texture.C_hex_color);
//             y++;
//         }
        
// // Texturizar la pared
//         t_image *texture = get_wall_texture(ray, gdata);  // Obtener la textura correcta segun si el rayo impacta en una pared norte, sur, este u oeste, ya que la textura debe ser diferente.
        
//         // Calcular la coordenada horizontal en la textura (tex_x)
//         double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
//         if (ray->line_crossing == 0)  // Pared vertical
//         {
//             wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_height;  // Usar la coordenada Y del punto de impacto. Osea miro en que pixel colisiona del eje Y y luego lo divido por el tamaño en pixeles de una casilla en el minimapa (representacion 2d) para saber en que parte de esa casilla esta colisionando. Ej: si colisiona en la casilla 4,75, significa que dentro de la casilla 4 choca en el 75% de esa casilla (entendiendo una casilla como el 100%). Nos quedamos solo con ese 75, porque indica que parte de la textura debemos pintar, me da igual el numero de la casilla
//         	//printf ("casilla de colision para textura |%f|\n", wall_x);
//         }
//         else  // Pared horizontal
//         {
//             wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;  // Usar la coordenada X del punto de impacto. esa coordenada corresponde a la columna en el eje x de la textura que debera pintarse
//         	//printf ("casilla de colision para textura |%f|\n", wall_x);
//         }
        
//         wall_x = wall_x - floor(wall_x);  // Parte fraccional de la posición dentro de la casilla --> Elimina la parte entera de wall_x y se queda solo con la fracción decimal. Queremos saber dentro de la casilla en qué punto impacta el rayo. Por ejemplo, si wall_x = 4.75, significa que el rayo impactó en la casilla 4, pero dentro de esa casilla impactó en el 75% de su ancho. Nos quedamos solo con 0.75

//         //Convertir la coordenada de wall_x en una coordenada en píxeles dentro de la textura --> Las texturas tienen un ancho fijo, por lo que si wall_x = 0.75 y la textura tiene 64 píxeles de ancho, entonces el rayo impactó en el píxel 48 de la textura.
//         int tex_x = (int)(wall_x * texture->xpm->texture.width);  // Coordenada horizontal en la textura
        
//         // Asegurar que tex_x esté dentro de los límites --> Si tex_x es menor que 0 o mayor que texture->width, intentar acceder a esos valores podría causar un segfault. Esto podria pasar por errores de redondeo y precision, y si pasa como mucho se repetira la primera o la ultima columna de la textura. Cuando estás muy cerca de la pared, el control de tex_x prácticamente nunca será un problema, porque solo estarás viendo una pequeña porción de la textura, y esa porción siempre estará dentro de los límites de la textura
//         if (tex_x < 0) 
//         	tex_x = 0;
//         if ((uint32_t)tex_x >= texture->xpm->texture.width) 
//         {
//         	tex_x = texture->xpm->texture.width - 1; // (- 1 porque em pieza en 0)
//         }

//         // Calcular cuánto de la textura debería saltarse si la pared es más grande que la pantalla --> Si la pared proyectada (wall_height) es más alta que la ventana (map.px_height), entonces parte de la textura debería "recortarse" para que solo se muestre el fragmento visible
// 		double tex_start_offset = 0; // tex_start_offset calcula cuántos píxeles de la textura hay que saltarse para centrar correctamente la imagen en pantalla.
// 		//Ej: 
// 			//Supongamos que wall_height = 1200 px y la ventana solo tiene map.px_height = 600 px.
// 			//Eso significa que 600 píxeles de la pared están fuera de la pantalla (300 arriba y 300 abajo).
// 			//Hay que empezar la textura en un punto más avanzado para evitar que la parte superior de la textura se muestre en la parte inferior de la pantalla

// 		if (wall_height > map.px_height)
// 		{
// 		    tex_start_offset = ((wall_height - map.px_height) / 2.0) * ((double)texture->xpm->texture.height / wall_height); 
// 		}
// 		//Si wall_height es más grande que la pantalla (map.px_height), hay una parte de la textura que no cabe en la pantalla.
// 		//wall_height - map.px_height calcula cuántos píxeles de más hay--> Si la pared proyectada tiene wall_height = 1200 píxeles, y la pantalla mide map.px_height = 800 píxeles. Esto significa que hay 400 píxeles de la textura que no pueden verse
// 		//En este caso, no queremos eliminar los 400 píxeles desde el inicio ni desde el final de la textura.
// 		//Queremos cortar la misma cantidad por arriba y por abajo para que la parte visible de la textura quede centrada en la pantalla.
// 		//Por eso dividimos entre 2, para repartir la parte que sobra mitad arriba y mitad abajo
// 				// ((wall_height - map.px_height) / 2.0) --> Calcula cuántos píxeles sobran en total y divide por 2.0 para saber cuánto hay que "cortar" arriba
// 		//Ahora necesitamos convertir los 200 píxeles en coordenadas de la textura.
// 			//texture->xpm->texture.height es la altura real de la textura.
// 			//wall_height es la altura proyectada en la pantalla.
// 			//(double)texture->xpm->texture.height / wall_height es un factor de escala para convertir los píxeles de la pantalla en píxeles de la textura
// 				//Ejemplo: Si la textura tiene una altura real de 256 píxeles y la pared proyectada (wall_height) es 1200 píxeles --> (256.0 / 1200) = 0.2133;
// 				//Ahora multiplicamos este factor por 200 (los píxeles que queremos saltarnos) --> tex_start_offset = 200 * 0.2133 = 42.67 ≈ 43 píxeles.
// 				//Esto significa que, para centrar la textura, debemos comenzar a dibujarla desde el píxel 43 de la textura real

// 				// * ((double)texture->xpm->texture.height / wall_height) --> Convierte esa cantidad de píxeles sobrantes a la escala de la textura. texture->xpm->texture.height / wall_height nos da la proporción de la textura que corresponde a un píxel en la pared.

//         // Dibujar la pared con textura correctamente alineada
//         double tex_y_ratio = (double)texture->xpm->texture.height / wall_height; // tex_y_ratio nos dice cuántos píxeles de la textura corresponden a un píxel en la pantalla. Si wall_height es grande, tex_y_ratio será menor (más detalle de la textura se verá)
//         while (y <= draw_wall_end) // Recorrer cada píxel en la pantalla dentro del rango de la pared (draw_wall_start hasta draw_wall_end)  y asignarle el color correcto de la textura.
//         {
//             // Calcular la coordenada vertical en la textura (tex_y) ajustando el punto de inicio
//             int tex_y = (int)((y - draw_wall_start) * tex_y_ratio + tex_start_offset); // Convierte la coordenada de la pantalla y en la coordenada de la textura tex_y. Se usa tex_start_offset para saltar los píxeles invisibles si la pared proyectada es demasiado alta

//             // Asegurar que tex_y esté dentro de los límites de la textura (Clamping de tex_y). Evita accesos fuera de los límites de la textura
//             if (tex_y < 0) 
//             	tex_y = 0;
//             if ((uint32_t)tex_y >= texture->xpm->texture.height) 
//             	tex_y = texture->xpm->texture.height - 1; // lo ajusta al último píxel válido (- 1 porque em pieza en 0)

//             // Obtener el color del píxel de la textura
//             int color = get_texture_pixel(texture, tex_x, tex_y);

//             // Dibujar el píxel en la pantalla
//             mlx_put_pixel(mlx.image, x, y, color);
//             y++;
//         }

//         // Dibujar el suelo
//         while (y < map.px_height)
//         {
//             mlx_put_pixel(mlx.image, x, y, gdata->texture.F_hex_color);
//             y++;
//         }

//         x++;
//     }
// }

/*
Cómo se adapta la textura según el tamaño de la pared y la pantalla
El código ya maneja bien el caso donde la pared es más grande que la pantalla con la variable tex_start_offset. Pero si la pared es más pequeña o más grande que la textura, hay otros factores a considerar.

🔹 Caso 1: La pared es más grande que la pantalla
✔ Qué pasa:

Si la altura calculada de la pared (wall_height) es mayor que la altura de la pantalla (map.px_height), significa que la pared sobresale de la pantalla.
Para evitar que la textura se estire mal, se calcula qué parte de la textura debería omitirse (tex_start_offset).
	double tex_start_offset = 0;
	if (wall_height > map.px_height)
	    tex_start_offset = ((wall_height - map.px_height) / 2.0) * ((double)texture->xpm->texture.height / wall_height);

Si la pared es más grande que la pantalla:
	Se calcula el exceso de altura (wall_height - map.px_height).
	Se traduce esa altura a la proporción dentro de la textura (texture->xpm->texture.height / wall_height).
	Se usa ese valor como un offset en la coordenada Y de la textura, saltándose la parte superior de la textura para que se vea correctamente centrada en la pantalla.


🔹 Caso 2: La pared es más pequeña que la pantalla
✔ Qué pasa:

Si wall_height < map.px_height, significa que la pared ocupa menos píxeles en la pantalla que el alto de la ventana.
No hay necesidad de hacer un tex_start_offset, pero la textura debe escalar correctamente.
✔ Cómo se maneja:

La variable tex_y_ratio ya ajusta la altura de la textura:

	double tex_y_ratio = (double)texture->xpm->texture.height / wall_height;
Si wall_height es pequeña, tex_y_ratio será grande, asegurando que la textura no se estire demasiado.


🔹 Caso 3: La pared es más grande o más pequeña que la textura
✔ Qué pasa:

Si la pared en pantalla (wall_height) es más grande que la textura, la textura se repetirá si el código lo permite.
Si la pared es más pequeña que la textura, solo se verá una parte de la textura.

✔ Cómo se maneja:
Normalmente, en juegos 3D se usa mapeo de texturas repetitivo (tiling) cuando la pared es más grande que la textura.
Si NO se quiere repetir, habría que clipear tex_y al tamaño de la textura:

	if ((uint32_t)tex_y >= texture->xpm->texture.height) 
	    tex_y = texture->xpm->texture.height - 1;

Si SÍ se quiere repetir, se puede usar el operador % para repetir la textura:

	tex_y = (int)((y - draw_wall_start) * tex_y_ratio + tex_start_offset) % texture->xpm->texture.height;

Esto hace que cuando tex_y supere texture->xpm->texture.height, vuelva a empezar desde 0.

🔹 Conclusión
📌 El código actual maneja bien si la pared es más grande que la pantalla.
📌 Si la pared es más pequeña que la pantalla, no se requiere ajuste extra.
📌 Si la pared es más grande que la textura, se puede decidir si repetirla o clipearla.

🔧 Si quieres que la textura se repita en paredes grandes, usa tex_y % texture->xpm->texture.height.*/


//VERSION 1, SOLO CON COLORES

// void print_map (t_game *gdata, t_mlx mlx, t_map map)
// {
	
//     int x = 0; 
// 	while (x < gdata->vision.FOV.num_rays)
//     {
//     	// Obtener el rayo precalculado
//         t_ray *ray = &gdata->vision.FOV.rays[x];

//         // Calcular la altura de la pared en píxeles
//         double wall_height = map.px_height / ray->perpendicular_distance; // altura total de la pantalla / distancia del jugador a la pared perpendiclarmente (para evitar ojo de pez). A menor distancia, la pared será más alta; a mayor distancia, la pared será más baja
// // printf ("map.px_height %d\n", map.px_height);
// // printf ("ray->perpendicular_distance %f\n", ray->perpendicular_distance);

//          // Calcular los límites verticales de la pared
//         int draw_wall_start = (map.px_height / 2) - (wall_height / 2);
//         int draw_wall_end = (map.px_height / 2) + (wall_height / 2);

//         //Limitar un valor dentro de un rango permitido
//         //Si wall_height es muy grande, draw_wall_start podría volverse negativo, y draw_wall_end podría ser mayor que map.px_height, lo que haría que mlx_put_pixel() intentara acceder a píxeles fuera del rango de la imagen, causando el segfault
//         //Aseguramos que draw_wall_start nunca sea menor que 0 y que draw_wall_end nunca sea mayor que map.px_height - 1
//         if (draw_wall_start < 0) 
//         {
//         	draw_wall_start = 0;
//         }

// 		if (draw_wall_end >= map.px_height) 
// 		{
// 			draw_wall_end = map.px_height - 1;
// 		}

//         // Dibujar el cielo
//         int y = 0;
//         while (y < draw_wall_start)
//         {
//             mlx_put_pixel(mlx.image, x, y, gdata->texture.C_hex_color);
//             y++;
//         }

//         // Dibujar la pared pintando en colores
//         while (y <= draw_wall_end)
//         {
//             //Determinar el color de la pared en función de la orientación
//             int wall_color;
//             if (ray->line_crossing == 0)
//             {
//                 if (ray->x_sign == 1)
//                     wall_color = NORTH_WALL_COLOR;
//                 else
//                     wall_color = SOUTH_WALL_COLOR;
//             }
//             else
//             {
//                 if (ray->y_sign == 1)
//                     wall_color = EAST_WALL_COLOR;
//                 else
//                     wall_color = WEST_WALL_COLOR;
//             }
//             mlx_put_pixel(mlx.image, x, y, wall_color);
//             y++;
//         }

//         // Dibujar el suelo
//         while (y < map.px_height)
//         {
//             mlx_put_pixel(mlx.image, x, y, gdata->texture.F_hex_color);
//             y++;
//         }

//         x++;
//     }
// }
