/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:13:51 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 14:15:42 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Busca la primera aparición de la subcadena needle en la cadena haystack 
//con una longitud máxima de len caracteres.
////
//Pasos: 
//1. Encontrar las posiciones de start (donde la letra en la que estoy 
//es n[0] --> importante definir que tenga en cuenta el \0 para que no se 
//salga del string y tambien que la i sea menor al len para que si encuentro 
//un start en la posicion x y la palabra que busco mide 5, pero solo me quedan
//3 de len para poder seguir comparando,  no deberia encontrar la palabra, 
//no deberia seguir comparando nada. 
//2. Si encuentro el needle me devuelve 1, sino 0

#include "libft.h"

static int	is_the_needle_here(const char *h, const char *n,
								size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (h[i] == n[j] && n[j] != '\0' && i < len)
	{
		i++;
		j++;
	}
	if (n[j] == '\0')
	{
		return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t		i;

	i = 0;
	if (n[0] == '\0')
		return ((char *)h);
	while (i < len && h[i] != '\0')
	{
		if (n[0] == h[i])
		{
			if (is_the_needle_here(h, n, i, len) == 1)
				return ((char *)&h[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const char *haystack = "holalaamila";
	const char *needle = "ami";
	//const char *haystack = "";
	//const char *needle = "ame";
	size_t len = -1;
	char *resultado;
	char *res;

	resultado = strnstr(haystack, needle, len);
	printf("resultado de la funcion original: %p\n", resultado);
	printf("%ld\n\n", resultado - haystack);
	res = ft_strnstr(haystack, needle, len);
	printf("resultado de mi funcion: %p\n", res);
	printf("%ld\n\n", res - haystack);
	return (0);
}*/
