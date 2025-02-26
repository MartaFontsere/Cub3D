/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:07:58 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 17:01:38 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve una nueva cadena que es una subcadena de la cadena s, comenzando en 
//el índice start y con una longitud máxima de len.
//
//Hay que tener en cuenta 3 casos distintos en funcion de los cuales 
//cambiara la cantidad de memoria que voy a reservar (IMPORTANTE)
	// 1. Que el len sea mas grande que lo que en verdad voy a recortar
	// 2. Que el start este fuera ("devolveremos un substr de 1 posicion con 
	// contenido '\0'")
	// 3. Caso standard
	//
	// En funcion de esto la memoria a reservar va a cambiar, por eso tengo 
	// que preparar 3 mallocs distintos. Y como entrara en uno u otro, con 
	// una sola comprovacion final de si se ha hecho bien el malloc 
	// es suficiente.

/*size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}*/

#include "libft.h"

static char	*create_malloc(unsigned int start, size_t len, size_t len2)
{
	char	*sub;

	if (start > len2)
		sub = malloc(sizeof(char) * 1);
	else if (len2 < start + len)
	{
		sub = malloc(sizeof(char) * (len2 - start + 1));
	}
	else
		sub = malloc(sizeof(char) * len + 1);
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	int				j;
	size_t			len2;

	len2 = ft_strlen(s);
	sub = create_malloc(start, len, len2);
	if (!sub)
		return (NULL);
	i = 0;
	if (start > len2)
	{
		sub[i] = '\0';
		return (sub);
	}
	while (i < start)
		i++;
	j = 0;
	while (s[i] != '\0' && i < (len + start))
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
/*
int main(void)
{
	char const *s = "hola mundo";
	unsigned int start = 1;
	size_t len = 4;
	ft_substr(s, start, len);
	return (0);
}*/
//al start parlem de posicions, per tant comensa en 0
//
//DATO INTERESANTE:
//Si tens aixo:
	//sub[j] = s[i]
	//i++
	//j++
//podem simplificar-ho en una linia amb sub[j++] i s[i++], perque 
//el iterador  es diferent als dos costats del igual. Si els dos 
//fossin i no podria 
//
//D'altre banda, saber la diferencia entre:
	//sub[j++] = s[i++]
	//sub[++j] = s[i++]
//en el primer cas primer evaluo el valor de j i despres suma, i 
//en el segon cas al reves, primer sumo una posicio de j i despres 
//miro en quina posicio estic.
//El primer cas seria equivalent a:
	//sub[j] = s[i]
	//j++
	//i++

//El segon cas seria equivalent a:
	//j++
	//sub[j] = s[i]
	//i++
