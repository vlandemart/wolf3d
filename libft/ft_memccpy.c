/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:41:33 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 13:17:02 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && *(unsigned char*)(src + i) != (unsigned char)c)
	{
		*(unsigned char*)(dst + i) = *(unsigned char*)(src + i);
		i++;
	}
	if (i == n)
		return (NULL);
	*(unsigned char*)(dst + i) = *(unsigned char*)(src + i);
	return (dst + i + 1);
}
