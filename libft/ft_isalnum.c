/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 23:39:45 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/23 04:03:27 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c <= 255 && c >= 0)
		if (((unsigned char)c <= 'z' && (unsigned char)c >= 'a')
			|| ((unsigned char)c <= 'Z' && (unsigned char)c >= 'A')
			|| ((unsigned char)c <= '9' && (unsigned char)c >= '0'))
			return (1);
	return (0);
}
