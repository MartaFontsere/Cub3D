/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 22:49:05 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:07:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Devuelve un valor diferente de cero si el carácter 
// es alfanumérico (una letra o un dígito), y cero en caso contrario.

#include "libft.h"

int	ft_isalnum(int alpha_digit)
{
	if (ft_isdigit(alpha_digit) || ft_isalpha(alpha_digit))
		return (1);
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
	int alpha_digit = 25;
	int result;

	result = ft_isalnum(alpha_digit);
	printf("%d", result);
	return (0);
}*/
