/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:49:38 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/02 02:53:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Convierte un carácter en minúsculas a su equivalente en mayúsculas.

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - 32;
	}
	return (c);
}
/*Lo de arriba es cuando paso por valor

Esto es cuando paso por referencia
int ft_toupper_ref(int *c)
{
	if (*c >= 97 && *c <= 122)
	{
		*c = *c - 32;
	}	
	return (*c);
}


int main(void)
{
	int c;
	int result;
	
	c = 'a';
	result = ft_toupper (c);
	printf("%c\n", result);
	printf("%c\n", c);
	return (0);
}

	int z;

	z = 'a';
	result =ft_toupper_ref(&z);
	printf("%c\n", result);
	printf("%c\n", z);
	return (0);
}
*/
