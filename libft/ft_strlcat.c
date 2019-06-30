/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 21:13:37 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 13:44:00 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t avail;
	size_t lendst;
	size_t lensrc;

	lendst = 0;
	while (lendst < size && dst[lendst])
		lendst++;
	lensrc = ft_strlen(src);
	if (lendst >= size)
		return (lendst + lensrc);
	avail = size - 1 - lendst;
	j = 0;
	i = lendst;
	while (j < avail && src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (lendst + lensrc);
}
