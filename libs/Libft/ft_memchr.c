/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:42:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 19:31:04 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Busca la primera aparición del valor c en los primeros n bytes 
//de la memoria apuntada por s.
//
//Tener presente que hay que castear el resultado  porque mi variable
// es un constant void, pero la funcion me pide que retorne solo un void.
//  por otro lado al poner & indico que quiero la direccion de memoria de 
//  s[i], por lo que asi estoy pasando el puntero

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s2;

	i = 0;
	s2 = (unsigned char *)s;
	while (i < n)
	{
		if (s2[i] == (unsigned char)c)
			return ((void *)&s2[i]);
		i++;
	}
	return (NULL);
}

/*int main(void)
{
	char s[8] = "alojao";
	int c = 'o';
	size_t n = 7;
	char *result;
	char *result2;
	size_t k; //esto es para poder saber la posicion en numeros 
	naturales de donde esta la letra que busco. Para devover varios 
	valores en el return, devuelvo lo que me pide y creo un puntero 
	que al modificarlo 

	result = memchr (s, c, n);
	printf("resultado de la funcion original\n%s\n", result);
	printf("%p\n", result);
	printf("%ld\n\n", result - s);
	result2 = ft_memchr (s, c, n, &k);
	printf("resultado de mi funcion:\n%s\n", result2);
	printf("%p\n", result2);
	printf("%ld\n", result2 - s);
	printf("posicion: %ld\n", k);
	return (0);
}*/
