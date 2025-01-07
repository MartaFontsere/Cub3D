/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adapted_strjoin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 03:52:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	special_case(char **s1)
{
	*s1 = malloc(sizeof(char) * 1);
	if (!*s1)
		return (0);
	*s1[0] = '\0';
	return (1);
}

char	*adapted_strjoin(char *s1, char *s2)
{
	char	*fusion;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL)
		if (special_case(&s1) == 0)
			return (NULL);
	fusion = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!fusion)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	j = 0;
	while (s1[i] != '\0')
		fusion[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		fusion[i++] = s2[j++];
	fusion[i] = '\0';
	free(s1);
	return (fusion);
}
