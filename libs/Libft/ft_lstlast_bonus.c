/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 22:35:15 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 17:27:51 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;
	t_list	*last;

	tmp = lst;
	last = NULL;
	if (!lst)
		return (0);
	while (tmp != NULL)
	{
		last = tmp;
		tmp = tmp -> next;
	}
	return (last);
}
//
//Tenir en compte que quan surto del while tmp es null, pero com 
//ja no entra, no li cambia el valor a last i aixi mantinc la
//posicio del ultimo nodo amb last.

///otra manera de hacerlo
/*t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;
	

	tmp = lst;
	while (tmp && tmp->next) //ponemos la condicion de tmp a secas, porque 
							si lo que me pasan es una lista vacia, en el 
							momento que quiero mirar el next de un null, 
							el programa peta. asi lo protejo. Al ser un &&,
						   	si lo primero no se cumple ya no chequeo lo 
							segundo, asi no peta
		tmp = tmp -> next; //ara cuan es trenca el while temp es el ultim 
							element, ja que abans d'entrar comprovo que el 
							seguent no sigui null, per tant no avanso. Per 
							tant quan surto soc lultim.
	return (tmp);
}*/
