/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/27 22:14:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//PENDIENTE

int check_right_move(t_game *gdata, double target_x, double target_y)
{
    int cell_x, cell_y;
    double angle = gdata->player.ray.vision_angle + M_PI / 2;  // 90 grados a la derecha

    // Calculamos las nuevas coordenadas del jugador para la dirección 'derecha'
    double contour_x = target_x + gdata->player.radius * cos(angle);
    double contour_y = target_y + gdata->player.radius * sin(angle);

    // Convertimos las coordenadas en celdas del mapa
    cell_x = (int)(contour_x / gdata->minimap.cell_width);
    cell_y = (int)(contour_y / gdata->minimap.cell_height);

    // Verificamos si la celda en esa dirección tiene una pared ('1')
    if (gdata->map.matrix[cell_y][cell_x] == '1')
        return 0;  // Colisión detectada, no permitimos el movimiento.

    return 1;  // El movimiento es válido, no hay colisión.
}
// int check_right_move(t_game *gdata, double target_y, double target_x)
// {
//     int cell_x, cell_y;
//     double angle, angle_step;

//     // Rango de ángulos para moverse hacia la derecha (90° ± margen)
//     double start_angle = M_PI_2 - M_PI / 6; // 60°
//     double end_angle = M_PI_2 + M_PI / 6;  // 120°

//     angle = start_angle; // Comienza en el límite inferior del rango
//     angle_step = M_PI / 36; // Incremento en pasos pequeños (más pasos = más precisión)

//     while (angle <= end_angle)
//     {
//         double contour_x = target_x + gdata->player.radius * cos(angle);
//         double contour_y = target_y + gdata->player.radius * sin(angle);

//         cell_x = (int)(contour_x / gdata->minimap.cell_width);
//         cell_y = (int)(contour_y / gdata->minimap.cell_height);

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }

//     return 1; // Movimiento válido
// }

int check_left_move(t_game *gdata, double target_x, double target_y)
{
    int cell_x, cell_y;
    double angle = gdata->player.ray.vision_angle - M_PI / 2;  // 90 grados a la izquierda

    // Calculamos las nuevas coordenadas del jugador para la dirección 'izquierda'
    double contour_x = target_x + gdata->player.radius * cos(angle);
    double contour_y = target_y + gdata->player.radius * sin(angle);

    // Convertimos las coordenadas en celdas del mapa
    cell_x = (int)(contour_x / gdata->minimap.cell_width);
    cell_y = (int)(contour_y / gdata->minimap.cell_height);

    // Verificamos si la celda en esa dirección tiene una pared ('1')
    if (gdata->map.matrix[cell_y][cell_x] == '1')
        return 0;  // Colisión detectada, no permitimos el movimiento.

    return 1;  // El movimiento es válido, no hay colisión.
}

// int check_left_move(t_game *gdata, double target_y, double target_x)
// {
//     int cell_x, cell_y;
//     double angle, angle_step;

//     // Rango de ángulos para moverse hacia la izquierda (270° ± margen)
//     double start_angle = 3 * M_PI_2 - M_PI / 6; // 240°
//     double end_angle = 3 * M_PI_2 + M_PI / 6;  // 300°

//     angle = start_angle;
//     angle_step = M_PI / 36;

//     while (angle <= end_angle)
//     {
//         double contour_x = target_x + gdata->player.radius * cos(angle);
//         double contour_y = target_y + gdata->player.radius * sin(angle);

//         cell_x = (int)(contour_x / gdata->minimap.cell_width);
//         cell_y = (int)(contour_y / gdata->minimap.cell_height);

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }

//     return 1;
// }

int check_up_move(t_game *gdata, double target_x, double target_y)
{
    int cell_x, cell_y;
    double angle = gdata->player.ray.vision_angle;  // El ángulo de visión del jugador (hacia arriba inicialmente)

    // Calculamos las nuevas coordenadas del jugador para la dirección 'arriba'
    double contour_x = target_x + gdata->player.radius * cos(angle);
    double contour_y = target_y + gdata->player.radius * sin(angle);

    // Convertimos las coordenadas en celdas del mapa
    cell_x = (int)(contour_x / gdata->minimap.cell_width);
    cell_y = (int)(contour_y / gdata->minimap.cell_height);

    // Verificamos si la celda en esa dirección tiene una pared ('1')
    if (gdata->map.matrix[cell_y][cell_x] == '1')
        return 0;  // Colisión detectada, no permitimos el movimiento.

    return 1;  // El movimiento es válido, no hay colisión.
}


// int check_up_move(t_game *gdata, double target_y, double target_x)
// {
//     int cell_x;  //coordenadas en x de la celda que queremos verificar
//     int cell_y; //coordenadas en y de la celda que queremos verificar
//     double angle;       // Ángulo actual del rayo
//     double angle_step;  // Incremento del ángulo en cada iteración
//     double start_angle; // Inicio del trozo de circulo a evaluar si colisiona
//     double end_angle; // Final del trozo de circulo a evaluar si colisiona

//     // Define el rango de ángulos alrededor del vision_angle
//     start_angle = gdata->player.ray.vision_angle - M_PI / 6; // 30° a la izquierda
//     end_angle = gdata->player.ray.vision_angle + M_PI / 6;   // 30° a la derecha
//     angle_step = M_PI / 36; // Divide el rango de comprovacion en pequeños "pasos", osea segmentos (5° por ejemplo)(cuantos más segmentos, más preciso será)

//     angle = start_angle; // Comienza desde el ángulo inicial
//     // Mientras no hayamos recorrido los 60 grados definidos en funcion de a donde mira el jugador
//     while (angle <= end_angle)
//     {
//         // Calcula las coordenadas de la celda que queremos verificar
//         cell_x = (int)((target_x + gdata->player.radius * cos(angle)) / gdata->minimap.cell_width);
//         cell_y = (int)((target_y + gdata->player.radius * sin(angle)) / gdata->minimap.cell_height);

//         // Si alguna coordenada choca con una pared ('1'), hay colisión
//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         // Avanza al siguiente punto de la esfera, dentro del rango marcado
//         angle += angle_step;
//     }

//     // Si no ha habido colisión en el rango, permitimos el movimiento
//     return 1;
// }

int check_down_move(t_game *gdata, double target_x, double target_y)
{
    int cell_x, cell_y;
    double angle = gdata->player.ray.vision_angle + M_PI;  // 180 grados de diferencia para moverse hacia abajo

    // Calculamos las nuevas coordenadas del jugador para la dirección 'abajo'
    double contour_x = target_x + gdata->player.radius * cos(angle);
    double contour_y = target_y + gdata->player.radius * sin(angle);

    // Convertimos las coordenadas en celdas del mapa
    cell_x = (int)(contour_x / gdata->minimap.cell_width);
    cell_y = (int)(contour_y / gdata->minimap.cell_height);

    // Verificamos si la celda en esa dirección tiene una pared ('1')
    if (gdata->map.matrix[cell_y][cell_x] == '1')
        return 0;  // Colisión detectada, no permitimos el movimiento.

    return 1;  // El movimiento es válido, no hay colisión.
}


// int check_down_move(t_game *gdata, double target_y, double target_x)
// {
//     int cell_x, cell_y;
//     double angle, angle_step;

//     // Rango de ángulos para moverse hacia abajo (180° ± margen)
//     double start_angle = M_PI - M_PI / 6; // 150°
//     double end_angle = M_PI + M_PI / 6;  // 210°

//     angle = start_angle;
//     angle_step = M_PI / 36;

//     while (angle <= end_angle)
//     {
//         double contour_x = target_x + gdata->player.radius * cos(angle);
//         double contour_y = target_y + gdata->player.radius * sin(angle);

//         cell_x = (int)(contour_x / gdata->minimap.cell_width);
//         cell_y = (int)(contour_y / gdata->minimap.cell_height);

//         if (gdata->map.matrix[cell_y][cell_x] == '1')
//             return 0;

//         angle += angle_step;
//     }

//     return 1;
// }

// int	check_right_move(t_game *gdata, double target_y, double target_x)
// {
// 	int	tsize_minus_one;

// 	tsize_minus_one = gdata->minimap.cell_width - 1;
	
// 	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
// 			+ tsize_minus_one - gdata->player.radius) / gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
// 			/ gdata->minimap.cell_height)][(int)((target_x + tsize_minus_one - gdata->player.radius)
// 		/ gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	return (1);
// }

// int	check_left_move(t_game *gdata, double target_y, double target_x)
// {
// 	int	tsize_minus_one;

// 	tsize_minus_one = gdata->minimap.cell_width - 1;
// 	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
// 			+ gdata->player.radius) / gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
// 			/ gdata->minimap.cell_height)][(int)((target_x + gdata->player.radius)
// 		/ gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	return (1);
// }

// int	check_up_move(t_game *gdata, double target_y, double target_x)
// {
// 	int	tsize_minus_one;
// 	printf ("cell_width |%f|\n", gdata->minimap.cell_width);
// 	printf ("radio player |%f|\n", gdata->player.radius);
// 	printf ("target x a checkear |%f|\n", target_x);
// 	printf ("target y a checkear |%f|\n", target_y);
// 	printf ("revision target x final: |%d|\n", (int)((target_x + gdata->player.radius) / gdata->minimap.cell_width));
// 	printf ("revision target y final: |%d|\n", (int)((target_y + gdata->player.radius) / gdata->minimap.cell_height));


// 	tsize_minus_one = gdata->minimap.cell_width - 1;
// 	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
// 			+ gdata->player.radius) / gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	if (gdata->map.matrix[(int)((target_y + gdata->player.radius) / gdata->minimap.cell_height)][(int)((target_x
// 			+ tsize_minus_one - gdata->player.radius) / gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	return (1);
// }




// int	check_down_move(t_game *gdata, double target_y, double target_x)
// {
// 	int	tsize_minus_one;

// 	tsize_minus_one = gdata->minimap.cell_width - 1;
// 	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
// 			/ gdata->minimap.cell_height)][(int)((target_x + gdata->player.radius)
// 		/ gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	if (gdata->map.matrix[(int)((target_y + tsize_minus_one - gdata->player.radius)
// 			/ gdata->minimap.cell_height)][(int)((target_x + tsize_minus_one - gdata->player.radius)
// 		/ gdata->minimap.cell_width)] == '1')
// 		return (0);
// 	return (1);
// }

int	can_i_move_to(t_game *gdata, double target_x, double target_y)
{
	if (gdata->player.mov_right == 1)
	{
		if (check_right_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_left == 1)
	{
		if (check_left_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_up == 1)
	{
		if (check_up_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	else if (gdata->player.mov_down == 1)
	{
		if (check_down_move(gdata, target_y, target_x) == 0)
			return (0);
	}
	return (1);
}