/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:56:41 by njacobso          #+#    #+#             */
/*   Updated: 2018/12/05 20:57:10 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	free_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		list = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list_new;
	t_list *list_buf;

	if (!lst || !f)
		return (NULL);
	list_buf = f(lst);
	list_new = list_buf;
	while (lst->next)
	{
		lst = lst->next;
		if (!(list_buf->next = f(lst)))
		{
			free_list(list_new);
			return (NULL);
		}
		list_buf = list_buf->next;
	}
	return (list_new);
}
