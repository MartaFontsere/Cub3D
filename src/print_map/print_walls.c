/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 05:04:06 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 05:05:07 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_wall_column (t_game *gdata, t_ray *ray, double *wall_x)
{
    // Calcular la coordenada horizontal en la textura (tex_x)
    if (ray->line_crossing == 0)  // Pared vertical
        *wall_x = ray->px_collision_y / gdata->minimap.px_in_cell_width;  // Usar la coordenada Y del punto de impacto. Osea miro en que pixel colisiona del eje Y y luego lo divido por el tamaño que le he dado a la cuadricula del mapa 3D para tener una escala unificada en todo el mapa, y en mi caso coincide con el tamaño de una casilla del minimapa (SI QUISIERA TENER UN VALOR STANDAR Y CUADRADO, PODRIA CAMBIARLO POR UN TILE_SIZE UNIFICADO, pero tambien tendria que aplicarlo en el calculo del FOV). Esto es para saber en que parte de esa casilla esta colisionando. Ej: si colisiona en la casilla 4,75, significa que dentro de la casilla 4 choca en el 75% de esa casilla (entendiendo una casilla como el 100%). Nos quedamos solo con ese 75, porque indica que parte de la textura debemos pintar, me da igual el numero de la casilla
     ////printf ("casilla de colision para textura |%f|\n", wall_x);
    else  // Pared horizontal
        *wall_x = ray->px_collision_x / gdata->minimap.px_in_cell_width;  // Usar la coordenada X del punto de impacto. esa coordenada corresponde a la columna en el eje x de la textura que debera pintarse
     ////printf ("casilla de colision para textura |%f|\n", wall_x);
    
    *wall_x = *wall_x - floor(*wall_x);  // Parte fraccional de la posición dentro de la casilla --> Elimina la parte entera de wall_x y se queda solo con la fracción decimal. Queremos saber dentro de la casilla en qué punto impacta el rayo. Por ejemplo, si wall_x = 4.75, significa que el rayo impactó en la casilla 4, pero dentro de esa casilla impactó en el 75% de su ancho. Nos quedamos solo con 0.75
}

void get_texture_column(t_image *texture, double *wall_x, int *tex_x)
{
    //Convertir la coordenada de wall_x en una coordenada en píxeles dentro de la textura --> Las texturas tienen un ancho fijo, por lo que si wall_x = 0.75 y la textura tiene 64 píxeles de ancho, entonces el rayo impactó en el píxel 48 de la textura.
    *tex_x = (int)(*wall_x * texture->xpm->texture.width);  // Coordenada horizontal en la textura
    
    // Asegurar que tex_x esté dentro de los límites --> Si tex_x es menor que 0 o mayor que texture->width, intentar acceder a esos valores podría causar un segfault. Esto podria pasar por errores de redondeo y precision, y si pasa como mucho se repetira la primera o la ultima columna de la textura. Cuando estás muy cerca de la pared, el control de tex_x prácticamente nunca será un problema, porque solo estarás viendo una pequeña porción de la textura, y esa porción siempre estará dentro de los límites de la textura
    if (*tex_x < 0) 
        *tex_x = 0;
    if ((uint32_t)*tex_x >= texture->xpm->texture.width)
       *tex_x = texture->xpm->texture.width - 1; // (- 1 porque em pieza en 0)
}

void get_texture_row(t_game *gdata, t_image *texture,  double *tex_start_offset)
{
    // offset = desplazamiento. Calcular cuánto de la textura debería saltarse si la pared es más grande que la pantalla --> Si la pared proyectada (wall_height) es más alta que la ventana (map.px_height), entonces parte de la textura debería "recortarse" para que solo se muestre el fragmento visible
    *tex_start_offset = 0; // tex_start_offset calcula cuántos píxeles de la textura hay que saltarse para centrar correctamente la imagen en pantalla.
    //Ej: 
     //Supongamos que wall_height = 1200 px y la ventana solo tiene map.px_height = 600 px.
     //Eso significa que 600 píxeles de la pared están fuera de la pantalla (300 arriba y 300 abajo).
     //Hay que empezar la textura en un punto más avanzado para evitar que la parte superior de la textura se muestre en la parte inferior de la pantalla

    if (gdata->print_map.wall_height > gdata->map.px_height)
        *tex_start_offset = ((gdata->print_map.wall_height - gdata->map.px_height) / 2.0) * ((double)texture->xpm->texture.height / gdata->print_map.wall_height); 
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
}

void print_wall_column(t_game *gdata, int *row, int *column, t_image *texture, int tex_x, double tex_start_offset)
{
    double tex_y_ratio;
    int tex_y;

    // Dibujar la pared con textura correctamente alineada
    tex_y_ratio = (double)texture->xpm->texture.height / gdata->print_map.wall_height; // tex_y_ratio nos dice cuántos píxeles de la textura corresponden a un píxel en la pantalla. Si wall_height es grande, tex_y_ratio será menor (más detalle de la textura se verá)
    while (*row <= gdata->print_map.draw_wall_end) // Recorrer cada píxel en la pantalla dentro del rango de la pared (draw_wall_start hasta draw_wall_end)  y asignarle el color correcto de la textura.
    {
        // Calcular la coordenada vertical en la textura (tex_y) ajustando el punto de inicio
       tex_y = (int)((*row - gdata->print_map.draw_wall_start) * tex_y_ratio + tex_start_offset); // Convierte la coordenada de la pantalla y en la coordenada de la textura tex_y. Se usa tex_start_offset para saltar los píxeles invisibles si la pared proyectada es demasiado alta

        // Asegurar que tex_y esté dentro de los límites de la textura (Clamping de tex_y). Evita accesos fuera de los límites de la textura
        if (tex_y < 0) 
         tex_y = 0;
        if ((uint32_t)tex_y >= texture->xpm->texture.height) 
         tex_y = texture->xpm->texture.height - 1; // lo ajusta al último píxel válido (- 1 porque em pieza en 0)

        // Obtener el color del píxel de la textura
        gdata->print_map.color = get_texture_pixel(texture, tex_x, tex_y);

        // Dibujar el píxel en la pantalla
        mlx_put_pixel(gdata->mlx.image, *column, *row, gdata->print_map.color);
        (*row)++;
    }
}


// void print_door (t_game *gdata, t_ray *ray, int *row, int *column)
// {
//     double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
//     int tex_x;

//     double tex_start_offset;
//     t_image *texture;
//     // double door_perp_dist;
//     // int door_height, door_draw_start, door_draw_end;
//     // double door_recess;

//    // Usar la textura de la puerta
//     texture = &gdata->texture.door_img;
//     // Calcular la posición exacta de impacto en la casilla (wall_x)
//     get_wall_column(gdata, ray, &wall_x);
//     // Convertir wall_x a coordenada en la textura
//     get_texture_column(texture, &wall_x, &tex_x);
//     // Calcular el offset vertical en la textura para centrar la imagen
//     get_texture_row(gdata, texture, &tex_start_offset);
//     // Imprimir la columna de la puerta (la altura será la misma que la pared)
//     print_wall_column(gdata, row, column, texture, tex_x, tex_start_offset);
     
// }

// void print_texture_walls (t_game *gdata, t_ray *ray, int *row, int *column)
// {
//     double wall_x;  // Posición exacta donde el rayo impacta en la casilla, y por lo tanto su correspondencia en la pared, en que columna dentro de la unidad de la casilla.
//     int tex_x;

//     double tex_start_offset;
//     t_image *texture;

//     if (gdata->map.matrix[ray->cell_collision_y][ray->cell_collision_x] == 'D')
//         print_door (gdata, ray, row, column);
//     else
//     {
//         texture = get_wall_texture(ray, gdata);  // Obtener la textura correcta segun si el rayo impacta en una pared norte, sur, este u oeste, ya que la textura debe ser diferente.
//         get_wall_column (gdata, ray, &wall_x);
//         get_texture_column(texture, &wall_x, &tex_x);
//         get_texture_row(gdata, texture, &tex_start_offset);
//         print_wall_column(gdata, row, column, texture,tex_x, tex_start_offset);
//     }
// }



void print_texture_walls(t_game *gdata, t_ray *ray, int *row, int *column)
{
    double wall_x;
    int tex_x;
    double tex_start_offset;
    t_image *texture;

    if (gdata->map.matrix[ray->cell_collision_y][ray->cell_collision_x] == 'D')
        {
            double door_x;
    get_wall_column(gdata, ray, &door_x);
    
    // Restar el offset para que la puerta se dibuje en el centro del hueco
    if (ray->line_crossing == 1) // Puerta en pared horizontal
        door_x -= (gdata->minimap.px_in_cell_width / 2.0);
    else // Puerta en pared vertical
        door_x -= (gdata->minimap.px_in_cell_height / 2.0);
    
    // Obtener la textura de la puerta
    t_image *door_texture = &gdata->texture.door_img;
    int tex_x;
    get_texture_column(door_texture, &door_x, &tex_x);
    double tex_start_offset;
    get_texture_row(gdata, door_texture, &tex_start_offset);
    
    *row = gdata->print_map.draw_wall_start;
    print_wall_column(gdata, row, column, door_texture, tex_x, tex_start_offset);
        }
    else
    {
        texture = get_wall_texture(ray, gdata);
        get_wall_column(gdata, ray, &wall_x);
        get_texture_column(texture, &wall_x, &tex_x);
        get_texture_row(gdata, texture, &tex_start_offset);
        print_wall_column(gdata, row, column, texture, tex_x, tex_start_offset);
    }
}
