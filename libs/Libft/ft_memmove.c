/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:46:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 17:45:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copia los primeros n bytes del área de memoria apuntada por 
//src al área de memoria apuntada por dest, protegiendo la superposición 
//de memoria. Empezaremos a copiar por delante o por detras segun se necesite
//
//Importante recordar que cuando voy disminuyendo la variable len cuando es 
//unsigned char, si pongo como condicion que sea mayor o igual a 0 en un while, 
//cuando llegue a 0 y comprueve si el siguiente valor es negativo, nunca 
//sucedera, porque de 0 pasa al numero maximo en positivo (nunca llega al 
//negativo). Por eso pongo como condicion que sea mayor a 0, y luego dentro 
//diga que se copie el len -1, ya que el largo 3 corresponde a la posicion 2.
// De este modo cuando el while copia el largo 1 y copia la posicion 0, al 
// restar una posicion mas y comprobar la condicion para volver a entrar en 
// el while, ve que el largo es 0 y ya no debe entrar y sale del bucle. Ya no 
// tenemos bucle infinito.

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	unsigned char			*d;
	const unsigned char		*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else if (d < s)
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
/*
int main (void)
{
	//char *src = strdup("holis");
	//char *dst = strdup("bbbbbbbbbbbbbbb");
	//size_t	len = 9; 

	//char src [] = "holis"; 
	//char dst [100] = "";
	//char src [] = "holis";	
	//size_t	len = 200; 
	
	//char src [100] = ""; 
	//char dst [] = "holis";	
	//size_t	len = 8;
	
	//char src [3] = ""; 
	//char dst [] = "holis";	
	//size_t	len = 4; 

	//char src [] = "holis"; 
	//char dst [3] = "";	
	//size_t	len = 4; 

	
	//para poder imprimier el contenido de las direccines de memoria:
	char *src = strdup("holi \0que");
	char *dst = strdup("bbbbbbb\0bbbbbbb");	// necesito el strdup para 
	poder modificarlo, no puede ser solo *dst o *src.
	char *dst_2 = strdup("bbbbbbb\0bbbbbbb");
	size_t len = 7;

	dst = ft_memmove(dst, src, len);
	dst_2 = memmove(dst_2, src, len);
	printf("direccion de memoria src: %p\n", dst);
	printf("direccion de memoria dst: %p\n", src);
	printf("me: %s\n", dst);
	printf("or: %s\n\n", dst_2);
	size_t i = 0;

	while (i < 40) // pones un while para pode recorrer todo 
	el string,que no te imprima solo el contenido de la 
	primera posicion a donde apunta. 
	El tema es que a partir del primer \0 lo interpreta como 
	caracteres ocultos y para poder verlos tengo que ejecutar
   	el programa con un ./a.out|cat -e, asi muestra los 
	caracteres ocultos y veo que si imprime la cantidad de 
	veces que le pido, aunque no sepa el que.

	Le tengo que marcar yo un final al while, ya sea len 
	o la cantidad de bytes que quiera imprimir, porque 
	estoy hablando de memoria y aqui no para cuando 
	encuetra un \0 como en un string, sino que para cuando 
	yo le digo.
	importante tener en cuenta que un espacio no es un \0
	{
		printf("me: %d, expected: %d\n", dst[i], dst_2[i]);
		i++;
	}
	return (0);
}
*/
