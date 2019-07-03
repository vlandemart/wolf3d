/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcutc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 15:05:03 by njacobso          #+#    #+#             */
/*   Updated: 2019/06/09 15:05:14 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcutc(char *str, int n, int *len)
{
	char	*new;
	int		i;

	new = ft_strnew(n);
	i = 0;
	*len = 0;
	while (i < n && ft_isspace(str[i]) == 0)
	{
		new[i] = str[i];
		i++;
		*len += 1;
	}
	return (new);
}
