/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:38:25 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/02 16:41:46 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*clean_str(char *src, int start, int end, t_path *path)
{
	char	*str;
	
	path->p_count++;
	str = ft_substr(src, start, end);
	free(src);
	return (str);
}
