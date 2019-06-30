/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 22:01:07 by ydavis            #+#    #+#             */
/*   Updated: 2018/12/02 22:05:39 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_c(char *str, char c, size_t size)
{
	size_t	i;
	char	*tmp;

	if (!str)
	{
		if (!(tmp = (char*)malloc(sizeof(char) * 2)))
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		return (tmp);
	}
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
	free(str);
	return (tmp);
}
