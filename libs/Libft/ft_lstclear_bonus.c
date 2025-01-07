/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 23:56:11 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/13 23:46:25 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Manera 1

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		(*lst) = tmp;
	}
}
//Esta manera es mejor porque aprovecho el null al que apunta mi puntero 
//para igualarlo a lst al final, no tengo que hacerlo a parte.

//Manera 2

/*void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*destroy;

	tmp = *lst;
	if (!lst || !del)
		return ;
	while (tmp)
	{  
		destroy = tmp;
		tmp = tmp -> next;
		del (destroy -> content);
		free (destroy);
	}
	*lst = NULL; // important per dirli al main que aquesta variable ara val null
}*/

//*lst = NULL posará el nostre punter first del main a NULl
//Perque si no quan torni al main tindrs un puntero first que apunta a un nodo y
//una llista que ja no existeix

//pero null directe? sense relacionar-ho amb cap dels punteros que he creat?
// Es que els punteros que he creat serveixen a la meva funcio, pero quan la
// funcio acaba els punteros de la funcio es destrueixes sols

//Lo mes importante a una llista en no perder qui es el primer
//
//
//pero en realitat... si ja he alliberat i eliminat... ja apunta com 
//a tal a null no?
//
//El que vull fer es eliminar tots els nodos despres del while
//
//osigui he eliminat a lo que apunta lst, encara que sigui a traves d'un 
//altre puntero
//
//Tindre que avisar al puntero first del main que ara ella es NULL, 
//perque ara es una llista buida
//Si no faig *lst = NULL, quan torni al main el puntero first del main
//estará apuntant a un nodo que ja no existeix
//I el que pasara es que cuan vulguis Fer algu amb aquella nodo que ja 
//no existeix doncs donara segfailt
