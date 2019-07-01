/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:55:35 by njacobso          #+#    #+#             */
/*   Updated: 2018/12/15 17:57:53 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordlen(char const *str, char splitter, int start_index)
{
	int i;
	int len;

	i = start_index;
	len = 0;
	while (str[i] && str[i] == splitter)
		i++;
	while (str[i] && str[i] != splitter)
	{
		i++;
		len++;
	}
	return (len);
}
