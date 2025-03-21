/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 23:10:07 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:18:06 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Devuelve un valor diferente de cero si el carácter es 
// un valor ASCII válido (0-127), y cero en caso contrario

#include "libft.h"

int	ft_isascii(int ascii)
{
	if (ascii >= 0 && ascii <= 127)
		return (1);
	return (0);
}
/*
int main(void)
{
	int ascii = 100; 
	int result;

	result = ft_isascii(ascii);
	printf("test: %d\n", result);
	printf("el ascii corresponde a: %c", ascii);
	return (0);
}*/
