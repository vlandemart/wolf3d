/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 19:19:23 by njacobso          #+#    #+#             */
/*   Updated: 2018/11/24 14:08:53 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*src;
	int		i;
	int		j;

	src = (char*)s2;
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (src[j] && j < (int)n)
		s1[i++] = src[j++];
	s1[i] = '\0';
	return (s1);
}
