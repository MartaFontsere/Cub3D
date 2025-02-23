/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:33:28 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:36 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//calcula el punto del suelo en el minimapa 2D usando la distancia del rayo y el ángulo de visión. Importante para la perspectiva

//ray es el rayo actual

double calculate_floor_distance(int row, t_ray *ray, t_game *gdata)
{
    // Usamos una proyección para convertir row en una distancia real en el mundo --> es una manera correcta de tener en cuenta la perspectiva y la distancia a medida que dibujas el suelo.
    double distance_to_floor = (gdata->player.height * gdata->vision.projection_factor) / (row - (gdata->map.px_height / 2));

    // Corregimos la distorsión aplicando la distancia perpendicular
    distance_to_floor = distance_to_floor / cos(ray->current_angle - gdata->vision.vision_angle);

    return (distance_to_floor);
}


void calculate_floor_point(double distance_to_floor, t_ray *ray, t_game *gdata, double *floor_x, double *floor_y)
{
    // Calcula la posición en el mundo del punto de suelo correspondiente a este píxel
    *floor_x = gdata->player.x + ray->dir_x * distance_to_floor;
    *floor_y = gdata->player.y + ray->dir_y * distance_to_floor;
}


void render_floor_pixel(int column, int row, t_game *gdata, double floor_x, double floor_y)
{
    int color;

    // Color basado en textura 

    int tex_x = (int)(floor_x * gdata->texture.floor_img.xpm->texture.width) % gdata->texture.floor_img.xpm->texture.width;
    int tex_y = (int)(floor_y * gdata->texture.floor_img.xpm->texture.height) % gdata->texture.floor_img.xpm->texture.height;
    color = get_texture_pixel(&gdata->texture.floor_img, tex_x, tex_y);

    // Pinta el píxel en pantalla
    mlx_put_pixel(gdata->mlx.image, column, row, color);
}

void draw_floor(int column, int row, t_game *gdata, t_ray *ray)
{
    double distance_to_floor; // distancia del player al pixel de suelo que queremos dibujar en pixeles
    double floor_x; //posicion del pixel en x
    double floor_y; //posicion del pixel en y

    //Como lo calculamos por cada pixel de la columna, iremos sobreescriviendo el valor a cada vuelta, no tiene sentido guardarlo en una estrucutra


    // Mientras queden píxeles de suelo por dibujar en esta columna
    while (row < gdata->map.px_height)
    {
    //while (row < gdata->map.px_height)
        printf ("1\n");
        // Calcula la distancia del píxel en el mundo 3D
        distance_to_floor = calculate_floor_distance(row, ray, gdata);

        // Calcula qué punto del mapa 2D corresponde a este píxel
        calculate_floor_point(distance_to_floor, ray, gdata, &floor_x, &floor_y);

        // Dibuja el píxel en pantalla
        render_floor_pixel(column, row, gdata, floor_x, floor_y);

        // Avanza al siguiente píxel de la columna
        row++;
    }
}




    


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