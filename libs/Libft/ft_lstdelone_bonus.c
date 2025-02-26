/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:28:45 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 17:24:40 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Tengo que liberar un nodo suelto, no me estan pasando una lista, ya es el 
//nodo solo. Porque si formara parte de una lista, destruir un nodo podria 
//afectar a la posicion de first, por lo que si fuera asi me pasarian un 
//doble puntero para poder modificarlo.
//
//Libero el contenido del nodo usando la funcion del, y luego libero la 
//memoria del nodo utilizando free.
//
//Tener en cuenta que en la funcion del no le mando solo lst, ya que lo
//que elimino es el content.

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst -> content);
	free(lst);
}
