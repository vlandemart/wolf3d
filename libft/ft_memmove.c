/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:09:54 by njacobso          #+#    #+#             */
/*   Updated: 2018/11/28 21:52:31 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (src == dst)
		return (dst);
	d = (char*)dst;
	s = (const char*)src;
	i = -1;
	if (s < d)
		while ((int)(--len) >= 0)
			d[len] = s[len];
	else
		while (++i < len)
			d[i] = s[i];
	return (dst);
}
