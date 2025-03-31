/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:30:43 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 02:10:19 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Convierte una cadena de caracteres que representa un número entero en su 
//equivalente numérico.
//Ej:
//// " 45" -> 45
// " 45" -> 45
// " 45 8" -> 45
// " +3" -> 3
// " ++3" -> 0 
// "" -> 0
// Resultado empieza en 0
// Me como los espacios iniciales (ver isspace)
// Si hay signo, lo cojo (solo uno). Hago que signo sea 1 si es positivo, 
// -1 si es negativo
// Mientras sea un digito, hago la linea magica. Despues del signo espero 
// un digito, si no lo es lo considero 0.
// devuelvo resultado * signo
//
// IMPORTANTE IR COMPILADO A CADA TROZO DE FUNCION QUE HAGA, PARA IR 
// RESOLVIENDO PROBLEMAS
//
// Nota: una variable la tienes que inicializar siempre, para que entre 
// donde entre la tenga disponible

// static int	ft_isspace(int c)
// {
// 	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
// 		|| c == '\r' || c == ' ')
// 	{
// 		return (1);
// 	}
// 	return (0);
// }

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signo;
	int	result;

	i = 0;
	result = 0;
	signo = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+')
	{
		i++;
	}
	else if (str[i] == '-')
	{
		i++;
		signo = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * signo);
}
/*
int main(void)
{
	printf("\nresultado de mi funcion: %d\n",ft_atoi("  -4859"));
	return (0);
}*/

//si en una funcion hablan de espacios en general se refiere a 
