/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:23:40 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/31 20:23:41 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinc(char *s1, char const *s2)
{
	int		size;
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = ft_strnew(size);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (s1[j])
			str[i++] = s1[j++];
		j = 0;
		while (s2[j])
			str[i++] = s2[j++];
	}
	ft_strdel(&s1);
	return (str);
}
