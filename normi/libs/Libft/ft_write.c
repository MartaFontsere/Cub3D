/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:30:43 by mfontser          #+#    #+#             */
/*   Updated: 2024/03/25 14:06:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(int fd, const char *str, int size)
{
	int	fucking_return;

	fucking_return = write(fd, str, size);
	fucking_return++;
}
