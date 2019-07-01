/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:21:32 by njacobso          #+#    #+#             */
/*   Updated: 2019/02/16 13:09:07 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*s;
	char	*d;

	if (src == dst)
		return (dst);
	s = (char*)src;
	d = dst;
	i = -1;
	while (++i < (int)n)
		d[i] = s[i];
	return (dst);
}
