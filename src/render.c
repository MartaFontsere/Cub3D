/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/10 14:15:01 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void render_game (void *param)
{
	t_game	*gdata;

	gdata = param;
 	printf ("hola %d\n", gdata->minimap.width);
}