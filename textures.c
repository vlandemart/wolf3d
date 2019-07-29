/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:12:01 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:57:35 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		anim_tx(t_wf *wf)
{
	return (TXT_VENT_1 + wf->anim_frame);
}

/*
**	Rather than storing whole texture in objects, we store
**	their index in textures array.
**	Returns color in tx_index texture in point {x, y}.
*/

int		get_tx(t_wf *wf, int tx_index, int x, int y)
{
	if (tx_index == TXT_IMG)
		tx_index = anim_tx(wf);
	return (wf->textures[tx_index][x + y * 32]);
}

void	init_textures(t_wf *wf)
{
	wf->textures = (int**)malloc(sizeof(int*) * 30);
	wf->textures[TXT_SKY]		= read_texture(wf, "texture_creator/sky.wolf");
	wf->textures[TXT_BRICK]		= read_texture(wf, "texture_creator/brick.wolf");
	wf->textures[TXT_WOOD]		= read_texture(wf, "texture_creator/wood.wolf");
	wf->textures[TXT_STONE]		= read_texture(wf, "texture_creator/stone.wolf");
	wf->textures[TXT_IMG]		= read_texture(wf, "texture_creator/img.wolf");
	wf->textures[TXT_VENT_1]	= read_texture(wf, "texture_creator/vent1.wolf");
	wf->textures[TXT_VENT_2]	= read_texture(wf, "texture_creator/vent2.wolf");
	wf->textures[TXT_FLOOR]		= read_texture(wf, "texture_creator/floor.wolf");
	wf->textures[TXT_LAMP]		= read_texture(wf, "texture_creator/lamp.wolf");
	wf->textures[TXT_BOX]		= read_texture(wf, "texture_creator/box.wolf");
	wf->textures[TXT_HEALTH]	= read_texture(wf, "texture_creator/health.wolf");
}
