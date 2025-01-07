/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 21:26:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 15:04:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Reserva un bloque de memoria para num elementos, cada uno de tamaño size, 
//e inicializa todos los bits a cero.
//
//Para entenderlo mejor primero veamos malloc:
	//malloc: estamos cogiendo una porcion de memoria y dicienole que ahora 
	//pertenece a este string:
	//
	//str = malloc(sizeof(char) * (ft_strlen(s) + 1)); -->el +1 es porque 
	//tengo que anyadir un espacio para el \0.
	//
	//si no tenemos tanto espacio como le pedimos al malloc, tenemos que 
	//proteger el malloc por si falla. vamos a comprovar que haya funcionado, 
	//y sino vamos a salir de la funcion.
	//
		//if (!str ) --> quiere decir: si el string no existe
			//return (0);
			//
//asi protegemos el malloc. si el malloc falla entra en este if y acaba 
//la funcion. No hay que liberar porque no hemos llegado a usar memoria. 
//Esto es estructura basica de malloc. 
//
//str = malloc(sizeof(char) * (5 + 1); 
//

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, size * count);
	return (str);
}
/*
int main(void)
{
	void	*str;

	str = ft_calloc(5, 4);
	int i = 0;
	printf("he hecho calloc:%s||\n", str);
	while(i < 2000000000) 
	{	
		printf("%d|", ((char *)str)[i]);
		i++;
	}
}
*/
