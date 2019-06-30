/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:18:08 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/30 23:10:07 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_memfree(t_list **new)
{
	t_list *tmp;

	if (!new)
		return (NULL);
	while (*new)
	{
		tmp = *new;
		if (tmp->content)
			free(tmp->content);
		*new = (*new)->next;
		free(tmp);
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*iter;

	if (!f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		tmp = f(lst);
		if (!new)
		{
			if (!(new = ft_lstnew(tmp->content, tmp->content_size)))
				return (NULL);
			iter = new;
		}
		else if (!(iter->next = ft_lstnew(tmp->content, tmp->content_size)))
			return (ft_memfree(&new));
		else
			iter = iter->next;
		lst = lst->next;
	}
	return (new);
}
