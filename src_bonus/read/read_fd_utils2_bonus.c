/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:38:25 by yanaranj          #+#    #+#             */
/*   Updated: 2025/04/01 11:58:36 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

char	*clean_str(char *src, int end, t_path *path)
{
	char	*str;

	path->p_count++;
	str = ft_substr(src, 0, end);
	free(src);
	return (str);
}
