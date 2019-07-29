/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:13:08 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/24 16:13:11 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstremove(t_list **alst)
{
	if (!*alst)
		return ;
	free((*alst)->content);
	free(*alst);
	*alst = (*alst)->next;
}
