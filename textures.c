#include "main.h"

int		anim_tx(t_wf *wf)
{
	return (TXT_VENT + wf->anim_frame);
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
	return wf->textures[tx_index][x + y * 32];
}

void	init_textures(t_wf *wf)
{
	wf->textures = (int**)malloc(sizeof(int*) * 9);
	wf->textures[0] = read_texture("texture_creator/brick.wolf");
	wf->textures[1] = read_texture("texture_creator/wood.wolf");
	wf->textures[2] = read_texture("texture_creator/stone.wolf");
	wf->textures[3] = read_texture("texture_creator/img.wolf");
	wf->textures[4] = read_texture("texture_creator/lamp.wolf");
	wf->textures[5] = read_texture("texture_creator/box.wolf");
	wf->textures[6] = read_texture("texture_creator/health.wolf");
	wf->textures[7] = read_texture("texture_creator/vent1.wolf");
	wf->textures[8] = read_texture("texture_creator/vent2.wolf");
}