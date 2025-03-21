/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:41:16 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/03 17:02:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Combina dos cadenas de caracteres s1 y s2 en una nueva cadena resultante.
//
//IMPORTANTE tener en cuenta que cuando una variable es const quiere decir 
//que no podemos modificara

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
/*
int main(void)
{
	char *s1 = "";
	char *s2 = 0;
	char *res = ft_strjoin (s1, s2);

	printf("resultado funcion: |%s|", res);
	return (0);
}

//si en uno d los strings me pasan un null, crashea, porque 
//no puedes recorrer null y ya en strlen peta. el strlen peta 
//porque si le pasas un null, en vez de decirte que es 0 peta para
// avisarte de que no tiene sentido. Yo puedo protegerlo para evitar 
// que crashee, pero eso ya es criterio propio.
*/
