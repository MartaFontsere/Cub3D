/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:07:40 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 12:09:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Concatena hasta size - 1 caracteres de la cadena src a la cadena dest,
//asegurándose de que la cadena resultante esté terminada con '\0'.
//
//El dstsize indica la longitud final que debera tener el string ya concatenado,
//en caso que sea superior al dst origial. Si el size es inferior devuelve el 
//dst original sin tocarlo.
//El resultado de la funcion es la suma del valor minimo entre la cantidad de 
//dst y dstsize + la cantidad de src.
//
//Concateno mientras la i sea menor a dstsize -1, por un lado es solo menor 
//porque el size empieza por uno y la i por 0, y le resto 1 porque reservo un 
//espacio para el \0

#include "libft.h"

static void	concat(size_t dstsize, const char *src, char *dst, size_t i)
{
	size_t	j;

	j = 0;
	while (i < dstsize - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	res;
	size_t	min;

	min = 0;
	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	if (i < dstsize)
	{
		min = i;
		concat (dstsize, src, dst, i);
	}
	else if (i >= dstsize)
		min = dstsize;
	while (src[j] != '\0')
		j++;
	res = min + j;
	return (res);
}
/*
int	main(void)
{
// si pongo *dst es memoria dinamica, y si la igualo a un 
// contenido concreto ya reservo lo que corresponde a eso,
// no puedo luego llamar a la funcion y anyadir mas. Si
// pongo [10] ya reservo los sitios que voy a necesitar 
// y luego tengo espacio para hacer la concatenacion. En 
// caso de que no supiera lo que me van a pasar, lo suyo 
// seria hacer un malloc para poder cambiar la cantidad 
// de memoria que ocupa el string final.

	char 		*dst = "Hola buenos dias"; 
	char		*dst2 = "Hola buenos dias";
	const char 	*src = ",que tal";
	size_t 		dstsize = 15;
	size_t		result;
	size_t		res;

	result = strlcat (dst2, src, dstsize);
	printf("resultado funcion original: |%zu|\n \
			concatenacion: |%s|\n\n", result, dst2);
	res = ft_strlcat (dst, src, dstsize);
	printf("resultado de mi funcion: |%zu|\n \
			concatenacion: |%s|\n", res, dst);
	return (0);
}*/
