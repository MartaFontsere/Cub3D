/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:40:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/05 01:26:20 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Aplica la función f a cada carácter de la cadena s, pasando el índice 
//y el carácter como argumentos, y devuelve una nueva cadena resultante.

//Ejemplo de funcion f
//static char	f(unsigned int n, char a)
//{
//	if (a >= 'a' && a <= 'z')
//		a = a - 32;
//	return (a);
//}

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	char	*s2;

	i = 0;
	while (s[i] != '\0')
		i++;
	s2 = malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
int main(void)
{
	const char *s = "Hola que ase";
	printf("%s",ft_strmapi(s, f));
	return (0);
}
*/
