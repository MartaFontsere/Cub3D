/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:37:37 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:08:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve un valor diferente de cero si el carácter 
//es un dígito decimal (0-9), y cero en caso contrario.

#include "libft.h"

int	ft_isdigit(int digit)
{
	if (digit >= '0' && digit <= '9')
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
int main(void)
{
	int digit = 65;
	int result;

	result = ft_isdigit(digit);
	printf("%d", result);
	return (0);
}*/
