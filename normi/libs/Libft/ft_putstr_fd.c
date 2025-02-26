/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 01:22:21 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/05 01:46:13 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Escribe la cadena s en el descriptor de archivo fd.

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/*
int main(void)
{
	int fd;
	char *s = "hola";
	
	fd = open("test.txt", O_RDWR | O_CREAT);
	if (fd < 0)
		return (0);
	ft_putstr_fd (s, fd);
	close(fd);
	printf("fd: |%d| ", fd);
	return (0);
}*/
