/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:38:25 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/06 19:17:12 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*clean_str(char *src, int start, int end, t_path *path)
{
	char	*str;

	if (path->c.is_path == 1 || path->f.is_path == 1)
		path->c_count++;
	else
		path->p_count++;
	str = ft_substr(src, start, end);
	free(src);
	return (str);
}
