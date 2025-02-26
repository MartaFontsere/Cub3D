/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:48:06 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 17:29:46 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
/*
int main()
{
	t_list *a;
	t_list *b;
	t_list *first;

	a = ft_lstnew(ft_strdup("soy nodo A"));
	first = a;
	b = ft_lstnew(ft_strdup("sou nodo B"));
	a->next = b;
	//b->next = NULL; // no cal perque ja en la estrctura diem que si no li 
	//dius lo contrari, el seguent apunta a null
	
	t_list *tmp;
	tmp = first;
	while(tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

*/
/* ESTO NO SE QUE ES
int i = 0;
while(s[i]])
	i++;

t_list *tmp = 
while(tmp)
{
	tmp = tmp->next;
}



*/
