/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:31 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

//calcula el punto del suelo en el minimapa 2D usando la distancia del rayo y el ángulo de visión. Importante para la perspectiva

//ray es el rayo actual

// double calculate_floor_distance(int row, t_ray *ray, t_game *gdata)
// {
//     // Usamos una proyección para convertir row en una distancia real en el mundo --> es una manera correcta de tener en cuenta la perspectiva y la distancia a medida que dibujas el suelo.
//     double distance_to_floor = (gdata->vision.camera_height_scale) / (row - (gdata->map.px_height / 2));

//     // Corregimos la distorsión aplicando la distancia perpendicular
//     distance_to_floor = distance_to_floor / cos(ray->current_angle - gdata->vision.vision_angle);

//     return (distance_to_floor);
// }



//VERSION 2

// double  deg_to_rad(double degrees)
// {
//     return (degrees * M_PI / 180.0);
// }
// // fmod es una función matemática en C que devuelve el resto de la división de dos números de punto flotante (double o float). Es decir, realiza una operación similar al operador % pero para números con decimales
// double  normalize_angle(double angle)
// {
//     angle = fmod(angle, 360);
//     if (angle < 0)
//         angle += 360;
//     return (angle);
// }

// // Asumimos que ya están definidos:
// // #define X 0
// // #define Y 1

// // Renderiza un píxel de suelo usando la textura, mapeando la posición 'hit' al rango de la celda.
// void render_floor(int x, int *y, float hit[2], t_game *gdata)
// {
//     int txt_pixel[2];
//     t_image *texture;

//     texture = &gdata->texture.floor_img;

//     // Calcular correctamente la posición dentro de la celda
//     double mod_x = fmod(hit[X], gdata->minimap.px_in_cell_width);
//     if (mod_x < 0) 
//         mod_x += gdata->minimap.px_in_cell_width;

//     double mod_y = fmod(hit[Y], gdata->minimap.px_in_cell_height);
//     if (mod_y < 0) 
//         mod_y += gdata->minimap.px_in_cell_height;

//     // Convertir coordenadas del mundo a coordenadas de textura
//     txt_pixel[X] = (int)((mod_x / gdata->minimap.px_in_cell_width) * texture->xpm->texture.width) % texture->xpm->texture.width;
//     txt_pixel[Y] = (int)((mod_y / gdata->minimap.px_in_cell_height) * texture->xpm->texture.height) % texture->xpm->texture.height;

//     int color = get_texture_pixel(texture, txt_pixel[X], txt_pixel[Y]);
//     mlx_put_pixel(gdata->mlx.image, x, *y, color);
// }

// // Calcula la distancia y la posición en el mundo (hit) para el suelo en la fila actual,
// // usando la proyección en perspectiva. Se utiliza la dimensión vertical de la celda para la proyección.
// void raycast_floor(float hit[2], int *y, t_ray *ray, t_game *gdata)
// {
//     double floor_dist;
//     double beta;
//     float corrected_dist;

//     // Normalizar el ángulo de beta
//     beta = ray->current_angle - gdata->vision.vision_angle;
//     beta = normalize_angle(beta);
//     if (beta > 180)
//         beta = 360 - beta;

//     // Corregir distancia para evitar distorsión "ojo de pez"
//     corrected_dist = ray->perpendicular_distance / cos(deg_to_rad(beta));

//     // Asegurar que no hay valores negativos en el denominador
//     if (*y <= gdata->map.px_height / 2)
//         return;

//     // Cálculo correcto de la distancia del suelo desde la base de la pared
//     floor_dist = (gdata->minimap.px_in_cell_height * corrected_dist) / 
//                 (2.0 * (*y - gdata->map.px_height / 2));

//     if (floor_dist < 0 || floor_dist > 10000) // Evita valores absurdos
//         return;

//     ray->pixel_distance_to_floor = floor_dist;

//     // Usar la posición de colisión de la pared como punto base
//     hit[X] = ray->px_collision_x + floor_dist * cos(deg_to_rad(ray->current_angle));
//     hit[Y] = ray->px_collision_y - floor_dist * sin(deg_to_rad(ray->current_angle));
// }


// // Función que integra el renderizado del suelo y el techo para una columna, 
// // usando un ciclo while (en caso de iterar píxel a píxel en la dirección vertical).
// // Se espera que la variable 'y' ya esté posicionada en la fila donde termina la pared.
// void draw_floor(int x, int *y, t_game *gdata, t_ray *ray)
// {
//     float hit[2];

//     raycast_floor(hit, y, ray, gdata);

//     if (*y >= gdata->map.px_height)
//         return;

//     render_floor(x, y, hit, gdata);
    
//     // Se incrementa la fila; si iteras píxel a píxel en la columna, este incremento se hará en cada iteración.
//     (*y)++;
// }

//VERSION 1
// Calcula la posición en el mundo del punto de suelo correspondiente a este píxel
// y añade un offset horizontal basado en la columna para que la textura avance.
void calculate_floor_point(double distance_to_floor, t_ray *ray, t_game *gdata, double *floor_x, double *floor_y, int column)
{
    // Calcula la posición base en el mundo para este píxel del suelo.
    double base_floor_x = gdata->player.x + ray->dir_x * distance_to_floor;
    double base_floor_y = gdata->player.y + ray->dir_y * distance_to_floor;

    // Calcula el offset horizontal.
    // Se basa en la diferencia entre la columna actual y el centro de la pantalla.
    // floor_horizontal_scale es un factor (definido en t_game) que debe ajustarse para que una celda del minimapa
    // se mapee correctamente a la textura del suelo.
    double horizontal_offset = ((column - (gdata->map.px_width / 2)) / (double)gdata->map.px_width) * gdata->minimap.px_in_cell_width;

    // Ajusta la coordenada del piso incorporando el offset.
    *floor_x = base_floor_x + horizontal_offset; // floor x es la posicion del pixel en el minimapa
    *floor_y = base_floor_y; //floor y es la posicion del pixel en el minimapa

     // printf("floor_x: %.2f, floor_y: %.2f\n", *floor_x, *floor_y);
     
}


void render_floor_pixel(int column, int row, t_game *gdata, double floor_x, double floor_y, int floor_tex_width, int floor_tex_height)
{
    // Color basado en textura 
    int color;

        
        // Mapear las coordenadas del mundo a la textura.
        int tex_x = (int)(floor_x * gdata->minimap.px_in_cell_width / 6) % floor_tex_width; // gdata->minimap.px_in_cell_width se usa como un valor constante en los diferentes calculos para escalar de manera coherente todas las medidas
        int tex_y = (int)(floor_y * gdata->minimap.px_in_cell_height / 5) % floor_tex_height;
        // Asegurarse de que los índices sean positivos.
        if (tex_x < 0) tex_x += floor_tex_width;
        if (tex_y < 0) tex_y += floor_tex_height;

        // Obtener el color del píxel de la textura.
        color = get_texture_pixel(&gdata->texture.floor_img, tex_x, tex_y);

//printf("Tex: (%d, %d)\n", tex_x, tex_y);
    //en lugar de acceder repetidamente a gdata->texture.floor_img.xpm->texture.width y gdata->texture.floor_img.xpm->texture.height en cada llamada (dentro del bucle), se pueden almacenar esos valores en variables locales una sola vez para mejorar el rendimiento
    
    // Dibuja el píxel en la pantalla en la posición (column, row)
    mlx_put_pixel(gdata->mlx.image, column, row, color);
}

void draw_floor(int column, int row, t_game *gdata, t_ray *ray)
{
    //double constant_factor = gdata->player.height * gdata->vision.projection_factor; COMO NO CAMBIA LA ALTURA, LO INICIALIZAMOS AL PRINCIPIO Y NO HACE FALTA RECALCULAR POR CADA RAYO
    
    // Calcula el factor de corrección para la perspectiva: corrige la distancia para compensar la distorsión de la perspectiva.
    double angle_correction_factor = 1.0 / cos(ray->current_angle - gdata->vision.vision_angle); // Se calcula el inverso del coseno de la diferencia de ángulos para la corrección de perspectiva. Hay que calcularlo para cada columna, ya que depende del angulo de cada rayo

    // Caché de dimensiones de la textura: se obtienen una sola vez.
        int floor_tex_width = gdata->texture.floor_img.xpm->texture.width;
        int floor_tex_height = gdata->texture.floor_img.xpm->texture.height;

    double distance_to_floor; // distancia del player al pixel de suelo que queremos dibujar en pixeles
    double floor_x; //posicion del pixel en x
    double floor_y; //posicion del pixel en y

//Como lo calculamos por cada pixel de la columna, iremos sobreescriviendo el valor a cada vuelta, no tiene sentido guardarlo en una estrucutra, para no ocupar mucha memoria en el programa

// Mientras queden píxeles de suelo por dibujar en esta columna
    while (row < gdata->map.px_height)
    {
        // Ajustar la proyección vertical, ya que a medida que te alejas del centro de la pantalla, la distancia cambia
        // Calcula la diferencia vertical entre el píxel actual (row) y el centro de la pantalla (o mapa).
        double denominator = row - (gdata->map.px_height / 2);
        
        // Calcula la distancia desde la camara (jugador) hasta cada pixel de suelo de esa columna en pixeles
        distance_to_floor = (gdata->vision.camera_height_scale * angle_correction_factor) / denominator;
        // Calcula las coordenadas en el mapa 2D para ese punto del suelo (a que punto del mapa corresponde ese pixel de suelo).
         calculate_floor_point(distance_to_floor, ray, gdata, &floor_x, &floor_y, column);
        // Dibuja el píxel del suelo en la pantalla.
        render_floor_pixel(column, row, gdata, floor_x, floor_y, floor_tex_width, floor_tex_height);

         // Avanza al siguiente píxel de la columna
        row++;
    }
}
    

//Optimizaciones para evitar, dentro de los bucles, el acceso repetido a campos de estructuras (como las dimensiones de la textura) y recalcular operaciones que no varían entre iteraciones.




// void calculate_floor_point(t_game *gdata, t_wray *ray_to_wall, t_fray *ray_to_floor, int row)
// {

//     // Usar la información del choque con la pared ya calculada en calculate_ray.
//     // Determinar el suelo visible entre la posición del jugador y ese punto de choque con la pared.
//     // Para cada pixel de la columna de la pantalla (debajo del punto de colisión de la pared), calcular su posición en el mundo y su profundidad correcta.




//     // La distancia desde el jugador hasta el punto del suelo que estamos calculando
//     ray_to_floor->cell_distance = gdata->player.height / (row - gdata->vision.center_y);
//         // row representa la coordenada vertical del píxel proyectado en la pantalla (del mapa en 3D) , es decir, qué tan alto o bajo está en la imagen que se muestra en la pantalla --> se usa para calcular a qué parte del suelo en el mundo 3D corresponde un píxel en la pantalla 2
//             //Si miras al suelo, los píxeles de la parte superior de la pantalla representan puntos lejanos en el suelo del mapa.
//             //Los píxeles en la parte inferior representan puntos cercanos a los pies del jugador.
//         //Por eso row es clave: nos dice dónde está el píxel en la pantalla 2D y nos ayuda a calcular su posición real en el mundo 3D.
        
//         // row - gdata->vision.center_y Es la diferencia entre la posición del píxel y el centro de la pantalla --> Cuanto más abajo, más grande es este valor, lo que significa que la distancia es mayor
//         // gdata->player.height Es la altura del jugador en el mundo --> Permite hacer la relación entre dónde miramos y la perspectiva correcta


//     // Corregimos la distancia para eliminar la distorsión en perspectiva
//     ray_to_floor->cell_distance /= cos(ray->current_angle - gdata->vision.vision_angle);

//     // Calculamos la posición real en el mundo del píxel del suelo
//     floor_x = gdata->player.x + ray_to_floor->cell_distance * ray->dir_x;
//     floor_y = gdata->player.y + ray_to_floor->cell_distance * ray->dir_y;

//     // Guardamos la posición del píxel del suelo para su renderizado
//     ray->px_collision_x = floor_x;
//     ray->px_collision_y = floor_y; 