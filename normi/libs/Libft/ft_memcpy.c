/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:18:12 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 16:48:41 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Copia los primeros n bytes del área de memoria 
//apuntada por src al área de memoria apuntada por dest.

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int main(void)
{
	char dst[3];
	const char src[5] = "Hola";
	size_t n = 3;
	char *result;

	result = ft_memcpy(dst, src, n);
	printf("%s", result);
	return (0);
}

int main(void)
{
	 char *dst[5];
	 const char *src[5];
	 src[0] = 'e';
	 src[1] = 'd';
	 src[2] = 'c';
	 src[3] = 'b';
	 src[4] = 'a';
	size_t n = 2; solo copiara uno porque el otro es el nul

	int i = -1;
	while (++i < 4){
	printf("en la posicion %d del puntero int tiene el valor de src -> %c\n", 
			i, src[i]); 
			}
	i = -1;
	while (++i < 4){
	printf("en la posicion %d del puntero int tiene el valor de dst -> %c\n", 
			i, dst[i]); 
			}
	memcpy(dst, src, n);
	printf("\n\n\nDespues de memset:\n\n");
	i = -1;
	while (++i < 4){
	printf("en la posicion %d del puntero int tiene el valor de src -> %c\n", 
			i, src[i]); 
			}
	i = -1;
	while (++i < 4){
	printf("en la posicion %d del puntero int tiene el valor de dst -> %c\n", 
			i, dst[i]); 
			}
	return (0);
}*/
