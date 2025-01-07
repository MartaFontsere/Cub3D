/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:20:19 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 18:02:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Llena los primeros len bytes de la memoria apuntada 
// por str con el valor especificado en c. 
//
// Recordar que un puntero sea tipo void no quiere decir "vacio", 
// sino que tiene potencial para ser cualquier cosa. 
// Ademas, para poder modificar un puntero tipo void primero 
// tengo que castearlo, en este caso a tipo char.
//
// Puedes devolver el str porque tambien es de tipo void. 
// Si es void no puedess modificarlo, pero lo que haces es 
// modificar otra variable que apunta al mismo sitio, 
// y acabas devolviendo esa variable inicial que has cambiado indirectamente. 
//
// Si el len es mayor que el string que paso, 
// la funcion original peta, por lo que la mia tambien

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*str2;
	unsigned char	c2;

	str2 = (unsigned char *) str;
	c2 = (unsigned char) c;
	i = 0;
	if (len != 0)
	{
		while (i < len)
		{
			str2[i] = c2;
			i++;
		}
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "Holaaa";
	int		c = 42;
	size_t	len = 3;
	char	*result;
	char	*res;

	res = memset(str, c, len);
	printf("funcion original: %s\n", res);
	result = ft_memset(str, c, len);
	printf("mi funcion: %s\n", result);
	return (0);
}
*/
