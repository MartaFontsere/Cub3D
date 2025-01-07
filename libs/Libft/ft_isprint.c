/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:09:22 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:20:11 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve un valor diferente de cero si el carácter es 
//imprimible (incluyendo espacios en blanco), y cero en caso contrario.

#include <stdio.h>

int	ft_isprint(int print)
{
	if (print >= 32 && print <= 126)
		return (1);
	return (0);
}
/*
int main(void)
{
	int print = 35;

	printf("test: %d", ft_isprint(print));
	return (0);
}
*/
