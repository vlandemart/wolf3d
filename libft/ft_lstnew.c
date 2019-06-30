/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 00:48:06 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/30 21:11:42 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_voidcpy(void const *content, size_t size)
{
	void	*new;
	size_t	i;

	if (!(new = malloc(sizeof(void) * size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(unsigned char*)(new + i) = *(unsigned char*)(content + i);
		i++;
	}
	return (new);
}

static t_list	*ft_memfree(t_list **new)
{
	if (*new)
		free(*new);
	return (NULL);
}

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new->content = (unsigned char*)NULL;
		new->content_size = 0;
	}
	else if (!(new->content = ft_voidcpy(content, content_size)))
		return (ft_memfree(&new));
	else
		new->content_size = content_size;
	new->next = NULL;
	return (new);
}
