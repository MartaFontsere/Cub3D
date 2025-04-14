/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:54:15 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/14 13:19:31 by yanaranj         ###   ########.fr       */
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
	ft_write (2, "\n", 1);
}
