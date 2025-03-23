/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:39:33 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 02:53:45 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Convierte un carácter en mayúsculas a su equivalente en minúsculas.

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c = c + 32;
	}
	return (c);
}
/*
int main(void)
{
	char result;

	result = ft_tolower('D'); //perque no estic passant una variable 
	com a tal, sino asigno un valor directament quan crido a la funcio
	printf("%c", result);
	return (0);
}*/
