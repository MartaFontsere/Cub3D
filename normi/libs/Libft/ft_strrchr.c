/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 01:25:58 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 17:55:22 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve un puntero al último carácter 'c' en la cadena str,
//o NULL si no se encuentra.
//
//Metodologia: como miramos del final al principio, 
//primero miramos si el ultimo char es \0 y coincide con c 
//(porque empezamos desde el final). Si no lo es, le restamos 
//uno a i y seguimos comprovando de atras adelante dentro del while
//
//Casteamos el resultado porque asi en el propio return devolvemos 
//el puntero de la posicion que hemos encontrado --> convertimos el 
//contenido de s[i] a puntero a la vez que lo mandamos como return. 
//Creamos un nuevo puntero que hace que el string ahora sea desde 
//donde ha encontrado c en adelante. 

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	c2;

	c2 = (char)c;
	len = ft_strlen(s);
	i = len;
	if (c2 == '\0')
		return ((char *)&s[i]);
	i--;
	while (i >= 0)
	{
		if (s[i] == c2)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int main(void)
{
	char *s;
	char *result;
	int c = 'o';
	s = "Hola queo tal";
	result = ft_strrchr(s, c);
	printf("%s\n", result);
	
}*/
