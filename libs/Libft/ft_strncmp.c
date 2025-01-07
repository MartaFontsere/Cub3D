/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:50:47 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 13:02:16 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Compara los primeros n caracteres de las cadenas str1 y str2.
//
//
//Importante tener en cuenta por que 2 condiciones puede romperse el 
//while: porque la i sea igual a n o porque encuentre alguna diferencia 
//entre los dos strings. Lo que se retorna tendra que adaptarse a si se 
//encuentra un caso u otro.
//Retornamos unsigned char porque si es char normal y supera el 127, el
// siguiente se convierte en un numero negativo, y queremos que al comparar 
// diga que el ascii 125 es mayor que el 129.

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i < n && s1[i] != s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
int main(void)
{
	char *s1;
	char *s2;
	int n = 7;
	int result;
	int res;

	s1 = "holaa";
	s2 = "hol";
	result = strncmp (s1, s2, n);
	printf("su resultado: %d\n", result);
	printf("codigo ascii de e: %d\n", 'e');
	printf("codigo ascii de w: %d\n", 'w');
	printf("codigo ascii de i: %d\n", 'i');
	res = ft_strncmp (s1, s2, n);
	printf("mi resultado: %d\n", res);

	return (0);
}
//Lo que hace es, revisa si hay diferencias en las n letras que le indiques,
// y si las hay devuelve la diferencia entre ambas, sino da 0. Aunque haya 
// varias diferencias dentro de los n caracteres, se para
*/

//OTRA OPCION DE CODIGO:
/*
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return(0);
	while (i < n && s1[i] == s2[i] && s2[i])
	{
		i++;
	}
	if (i < n && s1[i] != s2[i]) 
		return((unsigned char)s1[i] - (unsigned char)s2[i]);

	return (0);
}
*/
