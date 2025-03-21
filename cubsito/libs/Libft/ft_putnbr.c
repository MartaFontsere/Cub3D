/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:21:05 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/12 01:06:21 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Escribe el número entero n en el descriptor de archivo fd.
//
// IMPORTANT else if, perque sino no funciona, li dono la opcio a que entri a
// tots els ifs, i no vull aixo, no mes vull que entri all cas que toca.

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		ft_write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_write(1, "-", 1);
		n = -n;
		ft_putnbr(n);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else if (n < 10)
	{
		n = n + '0';
		ft_write(1, (const char *)&n, 1);
	}
}
