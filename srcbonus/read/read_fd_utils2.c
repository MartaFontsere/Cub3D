/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:38:25 by yanaranj          #+#    #+#             */
/*   Updated: 2025/03/21 13:38:50 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*clean_str(char *src, int end, t_path *path)
{
	char	*str;

	path->p_count++;
	str = ft_substr(src, 0, end);
	free(src);
	return (str);
}
