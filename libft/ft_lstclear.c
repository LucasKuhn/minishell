/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalexk-ku <lalex-ku@42sp.org.br>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:05:24 by lalexk-ku         #+#    #+#             */
/*   Updated: 2021/08/13 15:05:24 by lalexk-ku        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Deletes and frees the given element and every
// successor of that element, using the function ’del’
// and free(3).
// Finally, the pointer to the list must be set to
// NULL.
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*next_cursor;

	if (!lst)
		return ;
	cursor = *lst;
	while (cursor)
	{
		next_cursor = cursor->next;
		ft_lstdelone(cursor, del);
		cursor = next_cursor;
	}
	*lst = NULL;
}
