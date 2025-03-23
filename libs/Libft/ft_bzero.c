/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:13:48 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/01 23:30:26 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Establece los primeros n bytes de la memoria apuntada por s a cero.
//Aqui no se retorna nada porque la funcion es void, que no es lo mismo 
//que si la funcion es void * (en ese caso retornas algo, 
//que puede ser de cualquier tipo)

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;
	int				i;

	i = 0;
	s2 = (unsigned char *)s;
	if (n != 0)
	{
		while (n > 0)
		{
			s2[i] = '\0';
			i++;
			n--;
		}
	}
}
/*
int main(void)
{
	char s[] = "holaaaaaaaaaaaa";
	size_t n = 4;
	char *result;
	char *res;
	
	printf("%s\n", s);
	ft_bzero(s, n);
	printf("Imprimiendo desde el principio: |%s|\n", s);
	printf("Imprimo desde la s[1] posicion |%s|\n", &s[1]);
	printf("Imprimo desde la s[2] posicion |%s|\n", &s[2]);
	printf("Imprimo desde la s[3] posicion |%s|\n", &s[3]);
	printf("Imprimo desde la s[4] posicion |%s|\n", &s[4]);
	printf("Imprimo desde la s[5] posicion |%s|\n", &s[5]);
	bzero(s, n);
	printf("Imprimiendo desde el principio: |%s|\n", s);
	printf("Imprimo desde la s[1] posicion |%s|\n", &s[1]);
	printf("Imprimo desde la s[2] posicion |%s|\n", &s[2]);
	printf("Imprimo desde la s[3] posicion |%s|\n", &s[3]);
	printf("Imprimo desde la s[4] posicion |%s|\n", &s[4]);
	printf("Imprimo desde la s[5] posicion |%s|\n", &s[5]);

	return (0);
}
*/
