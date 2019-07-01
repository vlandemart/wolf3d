/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 16:53:58 by njacobso          #+#    #+#             */
/*   Updated: 2018/12/15 16:54:29 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		simmilar;

	if (*needle == '\0')
		return ((char*)haystack);
	i = -1;
	simmilar = 0;
	while (haystack[++i] && !simmilar && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			k = i;
			simmilar = 1;
			while (haystack[k] && needle[j] && j < len && k < len)
				if (needle[j++] != haystack[k++])
					simmilar = 0;
			if (simmilar && !needle[j])
				return ((char *)haystack + i);
		}
	}
	return (NULL);
}
