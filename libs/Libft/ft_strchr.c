/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:57:49 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 12:51:45 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve un puntero al primer carácter 'c' en la cadena str, 
//o NULL si no se encuentra.
//
//IMPORTANTE: debo castear dese el principio para que compare chars con 
//chars, no solo en el return. El motivo es que si la c que me pasan se 
//sale del maximo numero en el codigo asci (el maximo char positivo es 
//127 y el maximo negativo es 128, pero si hablamos de unsigned char, 
//el maximo es 255), el ordenador tendria que comparar s[i] (que es 
//char), con lo que corresponde en int (ej: si me pasan el int 156, pero 
//en char solo puedo leer hasta dos digitos, tengo que decirle al ordenador 
//que de ese int solo lea el 56, para eso lo casteo a char, que sabe que 
//solo caben dos digitos (en este ejemplo) y podra comparar si realmente 
//s[i] es igual al char c. Si lo dejo en int nunca coincidira, el 
//ordenador no sabra compararlo).

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c2;

	c2 = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c2)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c2 == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*
int main()
{
	char *res;
	char *pos_in;
	
	pos_in = "hola que tal como estas\n";
	res = ft_strchr(pos_in, '\0');
	printf("%s\n", res);
	printf("posicion de memoria: %ld\n", (res - pos_in));
}

*/

/* Comprbacion 1 de main

int main()
{
	char *res;
	const char *pos_in;
	
	pos_in = (const char *)strdup("hola que tal como estas\n");
	res = ft_strchr(pos_in, '\0');
	printf("%s\n", res);
	printf("posicion de memoria: %ld\n", (res - pos_in));
}

 //printf("%c\n", res[0]);





 Paso 1 y 2


char *ft_strchr (const char *s, int c)
{
	int i;

	i = 0;
	
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			printf("He encontrado el caracter en la posicion %d\n", i);
			return(NULL);
		}
		i++;
	}
	return (NULL);
}


int main()
{
	char *res;
	res = ft_strchr("hola que tal como estas\n", 'a');
	printf("%s\n", res);
//	printf("%c\n", res[0]);
}*/

//A tener en cuenta para los returns:
//char c    c = '\0' es lo mismo que c = 0; //porque 
//el caracter nulo en asci vale 0
//char *s   s = '\0'   <-- MALL!!!!! a un puntero no 
//se le puede asignar como valor un caracter tiene que 
//ser una direccion de memoria
//char *s   s = NULL que es lo mismo que s = 0; porque 
//en los punteros un puntero NULL tiene el valor numerico 0

// El cero me vale para todos los casos char o char *
// Pero cuando leo el codigo, no veo tan claro si es un 
// char un char * o es un 0 de verdad perque el cero puede un numero
