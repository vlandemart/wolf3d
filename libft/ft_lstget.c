/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:24:22 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 12:27:31 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *list, int n)
{
	int i;

	i = 0;
	while (list->next)
	{
		if (i == n)
			return (list);
		i++;
		list = list->next;
	}
	return (NULL);
}
