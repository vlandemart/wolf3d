/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:27:12 by njacobso          #+#    #+#             */
/*   Updated: 2018/11/24 16:29:51 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*src;

	i = 0;
	src = (const char *)s;
	while (i < n)
	{
		if (*(src + i) == (char)c)
			return ((void *)src + i);
		i++;
	}
	return (NULL);
}
