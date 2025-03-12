/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:16:14 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 02:07:44 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Divide la cadena s en una matriz de cadenas utilizando el 
//carácter c como delimitador.
//
//Pasos para un split:
	//1. Contar palabras (IMPORTANTE0 --> ya sea buscando los inicios 
	//o finales de palabra
	//2. Reservar con malloc el array de (char*) + 1
	//3. Recorrer el str y empezar a cortar y pegar--> guardamos el substring 
	//en res posicion word. si "d" i start es 0, i end es 0, end - start es 0, 
	//por lo que le diria al substr que me cortara un len de 0, por eso cuando 
	//se calcula el len, siempre se hace end - start + 1;
	//4. Cerrar el array de char * poniendo el ultimo en NULL
	//5. Return matrix
	//6. Despues de devolver la matriz completa (despues de res[word]), 
	//protegeremos el malloc i si falla debemos limpiar la matriz que hemos
	// creado con free --> CONFIRMAR CON MARC

#include "libft.h"

static void	free_matrix(char **res, int num_col)
{
	while (num_col)
	{
		free(res[num_col - 1]);
		num_col--;
	}
	free(res);
}

static int	num_words(const char *s, char del)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != del && (s[i + 1] == del || s[i + 1] == '\0'))
			words ++;
		i++;
	}
	return (words);
}

static char	**matrix_words(char **res, const char *s, char del)
{
	int	i;
	int	start;
	int	word;
	int	j;

	i = 0;
	j = -1;
	word = 0;
	while (++j < num_words(s, del))
	{
		while (s[i] == del)
			i++;
		start = i;
		while (s[i] != del && s[i] != '\0')
			i++;
		res[word] = ft_substr(s, start, i - start);
		if (!res[word])
		{
			free_matrix(res, word);
			return (NULL);
		}
		word++;
	}
	res[word] = NULL;
	return (res);
}

char	**ft_split(char const *s, char del)
{
	int		words;
	char	**res;

	words = num_words (s, del);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = matrix_words(res, s, del);
	return (res);
}
/*
int main(void)
 {
 	char s[] = "hola buenos dias"; // si no li assigno memoria donara 
 							//segmentation fault. 
 							//Millor reservar memoria sempre amb []
 	char **split = ft_split(s, ' ');
 	int i;

 	i = 0;
 	while (split[i])
	{
 		printf("|%s|", split[i]);
 		i++;
 	}
 	return (0);
 }*/
