/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:14:58 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 20:06:37 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Compara los primeros num bytes de las áreas de memoria apuntadas 
//por s1 y s2.
//
//Como aqui comparamos memoria, no tenemos que controlar si el string llega a \0
//
//Cuando hacemos r[n-1], ir con cuidado en no entrar con n = 0, para eso 
//pongo la excepcion concreta.

#include "libft.h"
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*r1;
	unsigned char		*r2;
	int					res;

	i = 0;
	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	while (i < n && r1[i] == r2[i])
		i++;
	if (n == 0 || i == n)
		return (0);
	else
		res = r1[i] - r2[i];
	return (res);
}
/*
int main(void)
{
	char *s1 = "8909";
	char *s2 = "8908";
	size_t n = 8; 
	int result;	
	int res;

	result = memcmp(s1, s2, n);
	printf("%d\n", result);
	printf("numero ascii de 8: %d\n", '8');
	printf("numero ascii de 9: %d\n", '9');
	res = ft_memcmp(s1, s2, n);
	printf("%d\n", result);
	return (0);

}
*/
