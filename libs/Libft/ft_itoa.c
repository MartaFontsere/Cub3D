/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:57:45 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/06 19:45:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Convierte un número entero n a una cadena de caracteres y lo almacena en 
//el búfer proporcionado, utilizando la base especificada. Hay que gestionar 
//los numeros negativos.

// int ft_atoi(char *s);
// "42"   -> 42
// "   42a" -> 42

//Me dan un numero int, ex:  27
//Devuelvo una string "27", concretamente un char *

	//Necesito hacer un malloc pero de cuanto espacio?
	//hare una funcion que me de el numero de digitos que compone el 
	//numero + signo negativo si lo hay

	//Por eso me reservo en resultado malloc de char * ( numero de digitos 
	//que compone el numero + signo negativo si lo hay) + 1;

	// Lo de 7 + 48 = '7' , solo me sirve para digitos entre 0 - 9
	//
	// En el itoa necesito saber el len de mi numero para poder reservar el 
	// espacio con un malloc (ya que cuando lo convierto en un char* siempre 
	// necesitare reservar memoria).Para eso dividire el digito entre 10 tantas
	// veces como sea necesario para saber cuantos digitos tiene mi numero.
	//
	// Tener en cuenta que no podemos convertir numeros de mas de un digito a 
	// chars. Para eso tenemos que fragmentar los ints a su minima expresion y 
	// de ahi ya si podemos pasarlos a chars.
	//
	// Para generar el string voy restando el numero grande al resto del 
	// numero para irlo dividiendo de atras hacia adelante
	//
	//NOTA
	// tengo que poner el len del caso minimo, porque sino al pasar n a positivo
	//  no cabe y, aunque lo hace bien, paco da error. Lo mismo entre poner len
	//   10 o 11. No tiene mucho sentido pero en el min le da igual que guarde
	//    una posicion extra o no, en cambio en el caso negativo si no lo hago
	//     se queja.... Todo y guardar un espacio mas para el signo al hacer
	//     malloc....

#include "libft.h"

static int	len_num(int n)
{
	int	len;

	len = 1;
	if (n == -2147483648)
	{
		len = 11;
		return (len);
	}
	if (n < 0)
	{
		n = -1 * n;
		len++;
	}
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static int	get_exponent(int n)
{
	int	exp;

	exp = 1;
	while (n > 9)
	{
		n = n / 10;
		exp = exp * 10;
	}
	return (exp);
}

static char	*get_string(int n, char *string, int i, int len)
{
	int	exp;
	int	num;

	exp = 0;
	num = 0;
	while (n > 0)
	{
		exp = get_exponent(n);
		num = n / exp;
		string[i] = num + 48;
		n = n - (num * exp);
		i++;
		while ((len_num(n) < len - i && n != 0) || (n == 0 && i < len))
		{
			string[i] = '0';
			i++;
		}
	}
	string[i] = '\0';
	return (string);
}

static char	*ft_putchar(char *string, int n, int len)
{
	int	i;	

	i = 0;
	if (n == 0)
	{
		string[0] = '0';
		i++;
	}
	if (n == -2147483648)
	{
		n = 147483648;
		string[0] = '-';
		string[1] = '2';
		i++;
		i++;
	}
	if (n < 0)
	{
		n = n * (-1);
		string[0] = '-';
		i++;
	}
	string = get_string(n, string, i, len);
	return (string);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*string;

	len = len_num(n);
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	ft_putchar (string, n, len);
	return (string);
}
/*
int main(void)
{
	int n =-2147483648;
	char *itoa = ft_itoa (n);
	printf("resultado de itoa: |%s|\n", itoa);
	printf("len: |%d|", len_num(n));
	return (0);
}*/
/*
Funcion itoa que tenia antes, pero como contemplo el signo en 
el len lo he quitado de aqui:
char	*ft_itoa(int n)
{
	int		len;
	char	*string;
	//int		sign;

//	sign = 0;
//	if (n < 0)
//		sign = 1;
	len = len_num(n);
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	ft_putchar (string, n, len);
	return (string);
}
*/
