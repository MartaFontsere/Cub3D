/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 00:18:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/02/07 17:26:24 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	if (!lst || !f)
		return ;
	while (tmp)
	{
		f (tmp -> content);
		tmp = tmp ->next;
	}
}

// void	ft_lstadd_back(t_list **lst, t_list *new)
// {
// 	t_list	*tmp;
//
// 	tmp = *lst;
// 	if (tmp == NULL)
// 		*lst = new;
// 	else if (tmp != NULL)
// 	{
// 		while (tmp && tmp -> next)
// 			tmp = tmp -> next;
// 		tmp -> next = new;
// 	}
// }
// 
//  int	ft_lstsize(t_list *lst)
// {
// 	int		i;
// 	t_list	*tmp;
//
// 	i = 0;
// 	tmp = lst;
// 	while (tmp != NULL)
// 	{
// 		tmp = tmp -> next;
// 		i++;
// 	}
// 	return (i);
// }
//
// t_list	*ft_lstnew(void *content)
// {
// 	t_list	*new;
//
// 	new = malloc(sizeof(t_list));
// 	if (!new)
// 		return (NULL);
// 	new->content = content;
// 	new->next = NULL;
// 	return (new);
// }
//
// void to_upper_wrapper(void *content) {
//     char *str = (char *)content;
//     while (*str) {
//         *str = (char)ft_toupper((int)*str);
//         str++;
//     }
// }
//
// void to_lower_wrapper(void *content) {
//     char *str = (char *)content;
//     while (*str) {
//         *str = (char)ft_tolower((int)*str);
//         str++;
//     }
// }
//
// int main(int argc, char **argv)
// {
// 	int 	i = 1;
// 	t_list  *list = NULL;
// 	t_list  *tmp;
// 	t_list  *prova;
//
// 	while (i < argc)
// 	{
// 		prova = ft_lstnew(ft_strdup(argv[i]));
// 		if (list == NULL)
// 			list = prova;
// 		else
// 			ft_lstadd_back(&list, prova);
// 		i++;
// 	}
//
// 	i = 0;
// 	tmp = list;
// 	printf("ANTES\n");
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	tmp = list;
// 	ft_lstiter(list, to_upper_wrapper);
// 	printf("\n\n");
// 	printf("DESPUES\n");
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
//
// 	ft_lstiter(list, to_lower_wrapper);
//
// 	tmp = list;
// 	printf("\n\n");
// 	printf("DESPUES\n");
// 	while (tmp)
// 	{
// 		printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// }