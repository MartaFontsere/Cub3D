/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:32:30 by mfontser          #+#    #+#             */
/*   Updated: 2025/02/27 01:58:35 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
 #include "cub3D.h"

int rgb_to_hex(int r, int g, int b)
{
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;  // 0xFF para la opacidad (canal alfa)
}

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
    uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]; //para detectar los limites del color
    return color;
}