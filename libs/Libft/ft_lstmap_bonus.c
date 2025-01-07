/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:31:56 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 20:12:32 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*protect(void (*del)(void *), void *content, t_list *new_list)
{
	ft_lstclear(&new_list, del);
	free(content);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	void	*content;
	t_list	*new_nodo;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (protect (del, content, new_list));
		new_nodo = ft_lstnew(content);
		if (!new_nodo)
			return (protect (del, content, new_list));
		ft_lstadd_back (&new_list, new_nodo);
		lst = lst -> next;
	}
	return (new_list);
}
/*Revisar para hacer el codigo sin reciclar funciones:

		new_list = malloc(sizeof(t_list));
		first = new_list;
		if (!new_list)
		{
			while (new_list) //libero el contenido que ya tenga 
			almacenado de las otras iteraciones desde el principio.
			{
				destroy = first;
				first = first -> next;
				del (destroy -> content);
				free (destroy);
			}
			new_list = NULL;
			return (NULL);
		}
		new_list -> content = f(lst -> content);
		new_list = new_list -> next;
		lst = lst -> next;
	}
	return (new_list);
}*/
