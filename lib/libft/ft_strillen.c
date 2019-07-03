/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strillen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 15:44:00 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/21 15:45:59 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strillen(const char *s, char c, char i)
{
	size_t n;
	size_t sum;

	n = 0;
	sum = 0;
	while (s[n] && s[n] != c)
	{
		if (s[n] != i)
		{
			sum++;
			while (s[n] && s[n] != c && s[n] != i)
				n++;
		}
		while (s[n] && s[n] != c && s[n] == i)
			n++;
	}
	return (sum);
}
