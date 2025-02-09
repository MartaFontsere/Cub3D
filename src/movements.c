/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 01:16:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/09 20:55:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//PRINT MOVEMENT MINIMAPA

void print_player_FOV_in_motion(t_game *gdata, t_player player, double target_x, double target_y)
{
	printf ("hola%f\n", player.x);

	//calculate_fov(gdata, player.x, player.y);
	//print_FOV (gdata, gdata->vision, player.x, player.y, gdata->vision.last_vision_angle, DARK_GREY);
	print_minimap (gdata);
	calculate_fov(gdata, target_x, target_y);
	print_FOV (gdata, gdata->vision, target_x, target_y, gdata->vision.vision_angle,  SOFT_YELLOW);
}


void print_player_view_in_motion (t_game *gdata, t_player player, double target_x, double target_y)
{
	//print_vision_angle (gdata, player.x, player.y, gdata->vision.last_vision_angle, SOFT_YELLOW);
	printf ("player%f", player.x); // BORRAR
	print_vision_angle (gdata, target_x, target_y, gdata->vision.vision_angle, YELLOW1);
}


// Si dentro de la funcion print_player_FOV_in_motion tengo que se imprima primero en gris en la posicion que esta y que luego se repinte en amarillo en la posicion a la que se desplaza, no es lo mismo que lo de clear_screen? Es necesario? Ponme  toda el orden logico, el flujo de funciones, para saber en que orden se llaman y donde va cada parte del codigo



void print_player_move(t_game *gdata, t_player player, double target_x, double target_y)
{

	//print_player (gdata, player, player.x, player.y, DARK_GREY);
	print_player (gdata, player, target_x, target_y, RED1);
}

// void rotate_player(t_player *player) // rotate the player // importante que sea puntero para que se actualice el valor
// {
// 	if (player->rotate_right == 1)
// 	{
// 		printf ("angulo de rotacion1: |%f|\n", player->ray.vision_angle);
// 		player->ray.vision_angle += ROTATION_SPEED; // rotate right
// 		printf ("angulo de rotacion2: |%f|\n", player->ray.vision_angle);
// 		if (player->ray.vision_angle > 2 * M_PI) // Si el ángulo supera este valor, significa que el jugador ha completado una rotación completa. Para evitar que el valor siga aumentando sin control, lo "reinicias" restándole 2 * π, manteniendo el ángulo en el rango válido de 0 a 2 * π.
// 			player->ray.vision_angle -= 2 * M_PI; // Este reset asegura que el ángulo de orientación del jugador siempre esté contenido dentro de un círculo completo y no crezca indefinidamente
// 	}
// 	else if(player->rotate_left == 1)
// 	{
// 		player->ray.vision_angle -= ROTATION_SPEED; // rotate left
// 		if (player->ray.vision_angle < 0)
// 			player->ray.vision_angle += 2 * M_PI;
// 	}
// 	printf ("angulo de rotacion: |%f|\n", player->ray.vision_angle);
// }

void rotate_player(t_player *player, t_vision *vision)
{
    if (player->rotate_right == 1) // Rotar a la derecha (sentido horario)
    {
        printf("angulo de rotacion1 (derecha): |%f|\n", vision->vision_angle);
        vision->vision_angle += ROTATION_SPEED; // Aumentamos el ángulo (sentido horario)
        if (vision->vision_angle > 2 * M_PI) // Si el ángulo supera 2*PI, lo "reiniciamos"
            vision->vision_angle -= 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (derecha): |%f|\n", vision->vision_angle);
    }
    else if (player->rotate_left == 1) // Rotar a la izquierda (sentido antihorario)
    {
        printf("angulo de rotacion1 (izquierda): |%f|\n", vision->vision_angle);
        vision->vision_angle -= ROTATION_SPEED; // Restamos del ángulo (sentido antihorario)
        if (vision->vision_angle < 0) // Si el ángulo es menor que 0, lo "reiniciamos"
            vision->vision_angle += 2 * M_PI; // Aseguramos que el ángulo esté en el rango [0, 2π]
        printf("angulo de rotacion2 (izquierda): |%f|\n", vision->vision_angle);
    }
}


void	prepare_movement(t_game *gdata, t_vision vision, double *target_x, double *target_y)
{
	double	move_x;
	double	move_y;

	move_x = 0;
	move_y = 0;
	printf ("angulo 4 de rotacion: |%f|\n", vision.vision_angle);
	if (gdata->player.mov_up == 1) // Ir hacia adelante
	{
		move_x -= MOVE_SPEED * cos(vision.vision_angle);
		move_y -= MOVE_SPEED * sin(vision.vision_angle);
	}
	if (gdata->player.mov_down == 1) // Ir hacia atrás
	{
		move_x += MOVE_SPEED * cos(vision.vision_angle);
		move_y += MOVE_SPEED * sin(vision.vision_angle); 
	}
	 if (gdata->player.mov_right == 1) // Moverse a la derecha
    {
        move_x += MOVE_SPEED * cos(vision.vision_angle - M_PI_2);
        move_y += MOVE_SPEED * sin(vision.vision_angle - M_PI_2);
    }
    if (gdata->player.mov_left == 1) // Moverse a la izquierda
    {
        move_x += MOVE_SPEED * cos(vision.vision_angle + M_PI_2);
        move_y += MOVE_SPEED * sin(vision.vision_angle + M_PI_2);
    }
	// Solo actualizamos si no hay colisión
	if (check_collision(gdata, *target_x + move_x, *target_y + move_y))
	{
		*target_x += move_x;
		*target_y += move_y;
	}
	// Verificar los movimientos
    printf("movimiento | X: %f, Y: %f\n", move_x, move_y);
}

/*Explicacion signos

Caso: Movimiento hacia adelante (UP)
Cuando queremos avanzar en la dirección que el jugador está mirando (angle = vision_angle):

X:

cos(vision_angle) se suma (move_x += ...) porque queremos movernos hacia adelante en la dirección del ángulo.
Si el ángulo apunta hacia el Este (0°), el coseno es positivo y aumenta X.
Si el ángulo apunta hacia el Oeste (180°), el coseno es negativo y disminuye X.
Y:

sin(vision_angle) se resta (move_y -= ...) porque queremos que el jugador se mueva hacia arriba en coordenadas gráficas.
Si el ángulo apunta hacia el Norte (90°), el seno es positivo, y al restarlo, disminuimos Y (subimos).
Si el ángulo apunta hacia el Sur (270°), el seno es negativo, y al restarlo, aumentamos Y (bajamos).
Resumen:

cos controla el movimiento en el eje X: suma para Este, resta para Oeste.
sin controla el movimiento en el eje Y: resta para Norte (subir), suma para Sur (bajar).

Caso: Movimiento hacia atrás (DOWN)
Cuando queremos retroceder en la dirección opuesta a la que el jugador está mirando (angle = vision_angle):

X:

cos(vision_angle) se resta (move_x -= ...) porque estamos retrocediendo.
Si el ángulo apunta hacia el Este (0°), restar coseno disminuye X (retrocede).
Si el ángulo apunta hacia el Oeste (180°), restar coseno aumenta X (retrocede).
Y:

sin(vision_angle) se suma (move_y += ...) porque estamos retrocediendo en coordenadas gráficas.
Si el ángulo apunta hacia el Norte (90°), el seno es positivo, y al sumarlo, aumentamos Y (bajamos).
Si el ángulo apunta hacia el Sur (270°), el seno es negativo, y al sumarlo, disminuimos Y (subimos).
Resumen:

cos controla el eje X: resta para Este (retroceso), suma para Oeste (retroceso).
sin controla el eje Y: suma para Norte (bajar), resta para Sur (subir).


Caso: Movimiento hacia la derecha (RIGHT)
Cuando queremos movernos perpendicularmente hacia la derecha (angle = vision_angle - M_PI_2, es decir, 90° hacia la derecha de donde mira el jugador):

X:

cos(vision_angle - M_PI_2) se suma (move_x += ...) porque estamos moviéndonos hacia la derecha en el eje X.
Si el ángulo apunta hacia el Norte (90°), el coseno del ángulo desplazado (90° - 90° = 0°) es positivo y aumenta X.
Si el ángulo apunta hacia el Oeste (180°), el coseno del ángulo desplazado (180° - 90° = 90°) es negativo y disminuye X.
Y:

sin(vision_angle - M_PI_2) se resta (move_y -= ...) porque estamos moviéndonos hacia arriba en coordenadas gráficas.
Si el ángulo apunta hacia el Norte (90°), el seno del ángulo desplazado (90° - 90° = 0°) es 0 y no afecta Y.
Si el ángulo apunta hacia el Este (0°), el seno del ángulo desplazado (0° - 90° = -90°) es negativo, pero lo restamos, haciendo que Y aumente (bajamos).
Resumen:

cos controla el eje X: suma para moverse a la derecha.
sin controla el eje Y: resta para moverse a la derecha.

Caso: Movimiento hacia la izquierda (LEFT)
Cuando queremos movernos perpendicularmente hacia la izquierda (angle = vision_angle + M_PI_2, es decir, 90° hacia la izquierda de donde mira el jugador):

X:

cos(vision_angle + M_PI_2) se suma (move_x += ...) porque estamos moviéndonos hacia la izquierda en el eje X.
Si el ángulo apunta hacia el Norte (90°), el coseno del ángulo desplazado (90° + 90° = 180°) es negativo y disminuye X.
Si el ángulo apunta hacia el Este (0°), el coseno del ángulo desplazado (0° + 90° = 90°) es positivo y aumenta X.
Y:

sin(vision_angle + M_PI_2) se resta (move_y -= ...) porque estamos moviéndonos hacia arriba en coordenadas gráficas.
Si el ángulo apunta hacia el Norte (90°), el seno del ángulo desplazado (90° + 90° = 180°) es 0 y no afecta Y.
Si el ángulo apunta hacia el Oeste (180°), el seno del ángulo desplazado (180° + 90° = 270°) es negativo, pero lo restamos, haciendo que Y aumente (bajamos).
Resumen:

cos controla el eje X: suma para moverse a la izquierda.
sin controla el eje Y: resta para moverse a la izquierda.



Resumen general de los signos
Adelante/Atrás (UP/DOWN):

cos afecta X directamente: suma al avanzar, resta al retroceder.
sin afecta Y inversamente: resta al avanzar, suma al retroceder.
Izquierda/Derecha (LEFT/RIGHT):

cos afecta X según el ángulo perpendicular: suma para ambos (con correcciones por el ángulo).
sin afecta Y inversamente, pero usa desplazamientos de ángulo. */




/*
- M_PI_2 / + M_PI_2 

En pocas palabras:

ray.vision_angle - M_PI_2: Calcula la dirección 90° hacia la derecha del ángulo de visión actual.
ray.vision_angle + M_PI_2: Calcula la dirección 90° hacia la izquierda del ángulo de visión actual.
Esto se basa en la geometría del círculo unitario (o trigonométrico) y cómo funciona la rotación angular en radianes.

Rotación angular y el círculo trigonométrico
En un sistema de coordenadas cartesianas con un círculo trigonométrico:

El ángulo ray.vision_angle representa la dirección hacia la que está mirando el jugador.

0 radianes (0°) apunta hacia el Este.
M_PI_2 radianes (90°) apunta hacia el Norte.
M_PI radianes (180°) apunta hacia el Oeste.
3 * M_PI_2 radianes (270°) apunta hacia el Sur.
Moverse hacia la derecha o la izquierda significa rotar 90° desde el ángulo de visión actual:

Hacia la derecha: restamos 90° (- M_PI_2).
Hacia la izquierda: sumamos 90° (+ M_PI_2).

¿Por qué - M_PI_2 para derecha y + M_PI_2 para izquierda?
Esto se debe a cómo las coordenadas y los ángulos están definidos:

Hacia la derecha (ray.vision_angle - M_PI_2):

Restar M_PI_2 hace que el ángulo gire en sentido horario en el círculo unitario.
Ejemplo:
Si el jugador está mirando hacia el Norte (M_PI_2 o 90°), entonces hacia la derecha será 0° (Este).
Si el jugador está mirando hacia el Este (0°), entonces hacia la derecha será 270° (Sur).
Esto alinea el movimiento con la dirección perpendicular a la derecha de la dirección actual del jugador.
Hacia la izquierda (ray.vision_angle + M_PI_2):

Sumar M_PI_2 hace que el ángulo gire en sentido antihorario en el círculo unitario.
Ejemplo:
Si el jugador está mirando hacia el Norte (M_PI_2 o 90°), entonces hacia la izquierda será 180° (Oeste).
Si el jugador está mirando hacia el Este (0°), entonces hacia la izquierda será 90° (Norte).
Esto alinea el movimiento con la dirección perpendicular a la izquierda de la dirección actual del jugador.
¿Qué ocurre si no usamos ± M_PI_2 correctamente?
Si intercambiamos los signos o no los aplicamos adecuadamente, el jugador se moverá en la dirección opuesta a la esperada para los movimientos laterales.

Por ejemplo:

Si usamos ray.vision_angle + M_PI_2 para el movimiento hacia la derecha, el jugador se moverá hacia la izquierda.
Si usamos ray.vision_angle - M_PI_2 para el movimiento hacia la izquierda, el jugador se moverá hacia la derecha.
Esto causaría un comportamiento incoherente con respecto a la dirección de visión.

Ejemplo práctico:
Imagina que el jugador está mirando en diferentes direcciones y se mueve hacia la derecha o izquierda:

El jugador mira al Norte (90°, M_PI_2):

Derecha: ray.vision_angle - M_PI_2 = 90° - 90° = 0° (Este).
Izquierda: ray.vision_angle + M_PI_2 = 90° + 90° = 180° (Oeste).
El jugador mira al Este (0°):

Derecha: ray.vision_angle - M_PI_2 = 0° - 90° = 270° (Sur).
Izquierda: ray.vision_angle + M_PI_2 = 0° + 90° = 90° (Norte).
El jugador mira al Sur (270°, 3 * M_PI_2):

Derecha: ray.vision_angle - M_PI_2 = 270° - 90° = 180° (Oeste).
Izquierda: ray.vision_angle + M_PI_2 = 270° + 90° = 360° = 0° (Este).
El jugador mira al Oeste (180°, M_PI):

Derecha: ray.vision_angle - M_PI_2 = 180° - 90° = 90° (Norte).
Izquierda: ray.vision_angle + M_PI_2 = 180° + 90° = 270° (Sur).
Conclusión:
ray.vision_angle - M_PI_2 siempre calcula la dirección hacia la derecha del jugador.
ray.vision_angle + M_PI_2 siempre calcula la dirección hacia la izquierda del jugador.
Esto funciona para cualquier orientación inicial porque las operaciones se basan en rotaciones en el círculo trigonométrico.
Este ajuste asegura que el movimiento lateral sea coherente y esté alineado correctamente con la dirección actual del jugador.
*/