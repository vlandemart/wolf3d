/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:15:42 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 18:27:01 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_realloc_c(char *str, char c, size_t size)
{
	size_t	i;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size - 1)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	return (tmp);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	if (!(tmp = (char*)malloc(sizeof(char))))
		return (NULL);
	*tmp = '\0';
	while (s1[i])
	{
		if (!(tmp = ft_realloc_c(tmp, s1[i], i + 1)))
			return (NULL);
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		if (!(tmp = ft_realloc_c(tmp, s2[i], j + i + 1)))
			return (NULL);
		i++;
	}
	return (tmp);
}
