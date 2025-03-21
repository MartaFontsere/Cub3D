/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:36:03 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 17:21:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*first;

	first = *lst;
	if (!new)
		return ;
	else if (first == NULL)
		*lst = new;
	else
	{
		new->next = first;
		*lst = new;
	}
}
/*
int main()
{
	t_list *first;
	t_list a;
	t_list b;

	//Lista original
	a.content = ft_strdup("soy A");
	b.content = ft_strdup("soy B");
	a.next = &b;
	b.next = NULL;
	first = &a;

	// Nuevo elemento a anadir
	t_list c;
	c.content = ft_strdup("soy C");
	c.next = NULL;

	//EJEMPLO CUANDO PASAMOS PUNTERO SIMPLE Y
	//NO DOBLE, DE PORQUE NO FUNCIONA BIEN
	// ft_lstadd_front_mala(first, &c);
	// printf("En el main cuando vuevlo de la funcion mala, 
	// el primero es |%s|\n", first->content);

	ft_lstadd_front(&first, &c);
	t_list *tmp;
	tmp = first;
	while(tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}*/
