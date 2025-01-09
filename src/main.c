/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:38:57 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/08 21:04:52 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int argc, char **argv)
{
	char **map;

	(void)argc;
	(void)argv;
	map = parsing_pre__yahaira();
	if(!map){
		write(2, "error generating the map matrix\n", 32);
		return 1;
	}
	// A partir de aqui me lo paso bien
	// instalar la mlx, y lanzar una pantalla del tamaño, x y, para ver que funciona
}
