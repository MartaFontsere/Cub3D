/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:14:01 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 01:03:33 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copia hasta size - 1 caracteres de la cadena src en la cadena dest, 
//asegurándose de que la cadena resultante esté terminada con '\0'.

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t sizedest)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (src != 0 && sizedest != 0)
	{
		while (src[i] != '\0' && i < sizedest - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	len = ft_strlen(src);
	return (len);
}

/*strlen seria:
 size_t  i = 0;
 i = 0;
 while (src[i] != '\0')
 	i++;
return (i);
 }


int main(void)
{
	char dest[5] = "Hola";
	char src[14] = "Helloo buenas";
	size_t sizedest = 3;
	size_t result;
	size_t result2;
	
	printf("dest = %s\n", dest);
	printf("src = %s\n", src);
	result = strlcpy(dest, src, sizedest); //para probar la funcion original
	result2 = ft_strlcpy(dest, src, sizedest);
	printf("resultado = %zu\n", result);
	printf("resultado original = %zu\n", result2);
	printf("dest = %s\n", dest);
	printf("src = %s\n", src);
}*/
