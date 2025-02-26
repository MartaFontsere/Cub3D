/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:37:12 by mfontser          #+#    #+#             */
/*   Updated: 2025/01/16 16:01:59 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

char	*gnl_strjoin(char *store, char *buffer);
int		gnl_strlen(char *string);
int		check_store(char *store);
char	*update_store(char *store);
char	*construct_line(char *store);
char	*fill_store(int fd, char *store);
char	*get_next_line(int fd);
char	*killer_text(char *string);

#endif
