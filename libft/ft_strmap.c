/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:32:25 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/30 23:15:23 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_len_c(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*tmp;

	if (!f || !s)
		return (NULL);
	i = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * ft_len_c(s) + 1)))
		return (NULL);
	*tmp = '\0';
	while (s[i])
	{
		tmp[i] = f(s[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
