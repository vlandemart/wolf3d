/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 00:07:20 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/30 02:17:02 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	player_find(t_wf *wf)
{
	int i;
	int j;

	i = 0;
	while (i < wf->map_size)
	{
		j = 0;
		while (j < wf->map_size)
		{
			if (!wf->map[i][j])
			{
				wf->pl->pos.x = i * SQLEN + SQLEN / 2;
				wf->pl->pos.y = j * SQLEN + SQLEN / 2;
				return ;
			}
			j++;
		}
		i++;
	}
	ft_putendl("Incorrect map, no place for player!");
	exit(1);
}
