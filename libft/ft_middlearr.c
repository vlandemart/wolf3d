/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middlearr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 21:57:45 by ydavis            #+#    #+#             */
/*   Updated: 2018/12/02 22:05:54 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_middlearr(int *arr, size_t size)
{
	double	ret;
	size_t	i;

	if (!arr || !size)
		return (0);
	i = 0;
	ret = 0;
	while (i < size)
	{
		ret += arr[i];
		i++;
	}
	return (ret / i);
}
