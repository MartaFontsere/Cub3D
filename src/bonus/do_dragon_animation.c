/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dragon_animation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 04:21:47 by mfontser          #+#    #+#             */
/*   Updated: 2025/03/12 21:49:51 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"






// void do_dragon_animation (t_game *gdata)
// {
// 	int	animation_speed;
// 	static int	fly_clock = 0;
// 	static int			index;

// 	animation_speed = 3;

// 	if (fly_clock >= animation_speed * 3)
// 		fly_clock = 0;

// 	index = fly_clock / animation_speed;
// 	mlx_delete_image(gdata->mlx.init, gdata->texture.dragon_img[index].data);
// 	mlx_image_to_window(gdata->mlx.init, gdata->texture.dragon_img[index].data,
// 				690, 1048);
// 	if (index == 2)

// 		fly_clock = 0;
// 	else
// 		fly_clock++;
// }

void do_dragon_animation(t_game *gdata)
{
    if (gdata->texture.dragon_img[0].data == NULL) 
        printf ("***************\n");

    int animation_speed = 2; // Intervalo de tiempo entre cambios de frame
    static int fly_clock = 0; // Temporizador para controlar el cambio de frame
    static int current_index = 0; // Índice actual de la imagen a mostrar
    static int last_index = -1; // Índice de la última imagen mostrada, inicializado a -1

    fly_clock++;
    if (fly_clock >= animation_speed * 4) // Reiniciar el reloj después de mostrar todos los frames
        fly_clock = 0;

    current_index = fly_clock / animation_speed; // Determinar qué imagen mostrar basado en el reloj de vuelo
printf ("current_index = %d\n", current_index);
printf ("last_index = %d\n", last_index);

    if (last_index != -1 && last_index != current_index) {
        // Solo eliminar la imagen anterior si no es la primera vez y si el índice ha cambiado
        mlx_delete_image(gdata->mlx.init, gdata->texture.dragon_img[last_index].data);
        gdata->texture.dragon_img[last_index].data = NULL;
    }

    // Cargar la nueva imagen (si no está ya cargada)
    if (gdata->texture.dragon_img[current_index].data == NULL) 
    {
        printf ("cargo imagen num %d\n", current_index);
        gdata->texture.dragon_img[current_index].data = mlx_texture_to_image(gdata->mlx.init, &gdata->texture.dragon_img[current_index].xpm->texture);
    }
    // Mostrar la nueva imagen
    mlx_image_to_window(gdata->mlx.init, gdata->texture.dragon_img[current_index].data, 430, 900);

    // Actualizar el último índice mostrado
    last_index = current_index;

}



