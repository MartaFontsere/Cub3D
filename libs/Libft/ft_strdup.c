/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:58:59 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 15:06:45 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Duplica una cadena de caracteres, asignando dinámicamente memoria para 
//la copia y devolviendo un puntero a la nueva cadena.

/*size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main(void)
{
	const char *s = "hola";
	
	char *str1:
	char *sty2:

	str1 = strdup(s);
	str2 = ft_strdup(s);
	printf("puntero de la funcion original: %p\n", str1);
	printf("resultado original: %s\n\n", str1);
	printf("puntero de mi funcion: %p\n", str2);
	printf("resultado: %s", str2);	
	return (0);
}
*/
