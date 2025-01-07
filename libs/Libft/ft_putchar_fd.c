/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 23:41:18 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/05 01:44:16 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Escribe el carácter c en el descriptor de archivo fd.

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int main(void)
{
	int fd;
	//char c;
    
	fd = open("test.txt", O_RDWR | O_CREAT);
	if(fd < 0)
		return (0);
	ft_putchar_fd('Z', 1);
	//read(fd, &c, 1);
	//if(c == 'a')
	//	printf("he leido una a");
	//else
	//	printf("he leido otra cosa")
	close(fd);
	return (0);

	//permisos open: https://www.geeksforgeeks.org/input-output
	//-system-calls-c-create-open-close-read-write/
}*/
