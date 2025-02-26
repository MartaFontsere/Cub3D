/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 22:19:49 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/05 11:07:23 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Aplica la función f a cada carácter de la cadena s, pasando el índice y la 
//dirección del carácter como argumentos.
//
//La diferencia con el strmapi es que no creas un string nuevo, simplemente 
//llamas a una funcion con los parametros del string y ella va haciendo los 
//cambios necesarios y te la devuelve cambiada (no es un string constant, es
//modificable)

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
