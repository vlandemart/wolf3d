/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:19:26 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 15:00:06 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	void *tmp;

	if (!(tmp = malloc(sizeof(size_t) * size)))
		return (NULL);
	while (size)
		*(unsigned char*)(tmp + --size) = (unsigned char)NULL;
	*(unsigned char*)tmp = (unsigned char)NULL;
	return (tmp);
}
