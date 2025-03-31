/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 19:51:16 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/04 20:32:57 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve una nueva cadena que es una copia de la cadena s, pero sin los 
//caracteres individuales de la string set que haya al principio y al final
//
//Pasos a seguir:
	//1.Buscar donde esta el start del corte (buscar la aguja en el pajar)
	//2.Buscar donde esta el end del corte (buscar la aguja en el pajar)
	//3. Construir un malloc
	//4. Copiar
//
//NOTA
//Cuando hago una funcion para valorar una condicion, lo que retorna lo 
//puedo usar directamente como condicion dentro de un shile o un if
//
//Si queremos ir al final de un string, recordar que sera strlen del 
//string -1, porque el len empieza en 1 y las posiciones en 0 y nos 
//saldriamos del string.
//
//Hay que proteger la funcion en caso de que en el string solo haya 
//delimitadores, porque en tal caso el start llegara hasta el final 
//y el end hasta el inicio, entonces como se cruzan posiciones peta. 
//Para evitar eso y protegerlo, podemos decir que el stopper de end 
//sera que mientras end sea mas pequenyo que start (en vez de poner 
//que sea mas pequenyo que 0), esto nos protege de todo, porque start 
//como poco estara en 0 y como mucho al final).

#include "libft.h"

static int	is_char_in_the_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		len;

	if (set[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (is_char_in_the_set(set, s1[start]) == 1 && s1[start] != '\0')
		start++;
	end = ft_strlen (s1) -1;
	if (end < 0)
		end = 0;
	while (is_char_in_the_set(set, s1[end]) == 1 && end >= start)
		end--;
	len = end + 1 - start;
	str = ft_substr(s1, start, len);
	return (str);
}
/*
int main(void)
{
	char const *s1 = "cccaaabacacacahola holacabcabbcabacbccabcab";
	char const *set = "abc";
	printf("resultado de mi funcion |%s|", ft_strtrim (s1, set));
	return (0);
}*/
//result: hola hol
