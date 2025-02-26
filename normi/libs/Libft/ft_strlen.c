/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:28:30 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:33:04 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve la longitud de la cadena de caracteres str, 
//excluyendo el carácter nulo '\0'.

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
/*
#include <stdio.h>

int main(void)
{
	char    *str;
	int     result;

	str = "Hola que tal";
	result = ft_strlen(str);
	printf("strlen es: %d", result);
	return (0);
}*/
