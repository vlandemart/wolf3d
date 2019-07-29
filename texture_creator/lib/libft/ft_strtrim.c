/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 16:50:44 by njacobso          #+#    #+#             */
/*   Updated: 2019/04/14 17:36:04 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (ft_isspace(s[start]))
		start++;
	while (end > 0 && ft_isspace(s[end - 1]))
		end--;
	if (end < start)
		end = start;
	str = ft_strnew(end - start);
	if (!str)
		return (NULL);
	ft_strncpy(str, (char*)s + start, end - start);
	return (str);
}
