/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
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

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
		ft_putnbr_fd (n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd (n / 10, fd);
		ft_putnbr_fd (n % 10, fd);
	}
	else if (n < 10)
		ft_putchar_fd (n + '0', fd);
}
/*
int main(void)
{
	int fd;
	int n = 456;
	fd = open("test4.txt", O_RDWR | O_CREAT);
	if(fd < 0)
		return (0);
	ft_putnbr_fd(n, fd);
	close(fd);
	return (0);
}*/
