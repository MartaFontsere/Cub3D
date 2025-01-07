/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:53:03 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/05 01:52:20 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Escribe la cadena s, seguida de un salto de línea, 
//en el descriptor de archivo fd.

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}
/*
int main(void)
{
	int fd;
	char *s = "hola bona tarda";
	fd = open("test2.txt", O_RDWR | O_CREAT);
	if(fd < 0)
		return (0);
	ft_putendl_fd(s, fd);
	close(fd);
	printf("fd |%d|", fd);
	return (0);
}*/

//para comrobar si funciona lo que hago es compilar y en la terminal hago un 
//cat del archivo y miro lo que se ha escrito dentro.
