/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 13:23:28 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/30 13:24:58 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(char *str, int n)
{
	char	*new;
	int		i;

	new = ft_strnew(n);
	i = 0;
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	return (new);
}
