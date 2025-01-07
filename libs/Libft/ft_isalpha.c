/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:50:45 by mfontser          #+#    #+#             */
/*   Updated: 2024/01/31 17:09:22 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Devuelve un valor diferente de cero si el carácter 
//es una letra alfabética, y cero en caso contrario.

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int main(void)
{
	int c = 65;
	int result;

	result = ft_isalpha(c);
	printf("%d", result);
	return (0);
}*/
