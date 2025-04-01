/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:35:09 by mfontser          #+#    #+#             */
/*   Updated: 2025/04/01 01:52:50 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	msg_error(char *msg, char *msg2)
{
	ft_write (2, RED, ft_strlen(RED));
	while (*msg)
		ft_write(2, msg++, 1);
	ft_write (2, END, ft_strlen(END));
	if (msg2)
	{
		ft_write (2, BLUE, ft_strlen(BLUE));
		while (*msg2)
			ft_write(2, msg2++, 1);
		ft_write (2, END, ft_strlen(END));
	}
}
