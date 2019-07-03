/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:29:15 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 12:30:05 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcount(t_list *list)
{
	int i;

	i = 0;
	if (list == NULL)
		return (0);
	if (list->content != NULL)
		i++;
	while (list->next)
	{
		i++;
		list = list->next;
	}
	return (i);
}
