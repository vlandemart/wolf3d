/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:07:15 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/24 16:07:17 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **alst)
{
	if (!*alst)
		return ;
	while ((*alst)->next != NULL)
	{
		ft_memdel(&((*alst)->content));
		free(*alst);
		*alst = (*alst)->next;
	}
	ft_memdel(&((*alst)->content));
	free(*alst);
	*alst = NULL;
}
