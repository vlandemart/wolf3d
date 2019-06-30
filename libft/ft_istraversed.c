/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istraversed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 22:19:22 by ydavis            #+#    #+#             */
/*   Updated: 2019/02/07 15:23:32 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_istraversed(int **arr, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (i != j && arr[i][j] != arr[size - i][size - j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
