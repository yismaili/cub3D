/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randeringWall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:51:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 23:27:15 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calcule_xoffset(t_struct	*cub)
{
	if (cub->ray.check == 1)
		cub->textureoffsetx = cub->ray.vrtclwallhity;
	else
		cub->textureoffsetx = cub->ray.horzwallhitx;
	cub->textureoffsetx /= cub->scaleheight;
	cub->textureoffsetx -= floor(cub->textureoffsetx);
	cub->textureoffsetx *= cub->texture_width;
}

void	draw_ceilling(t_struct	*cub)
{
	int	j;

	j = 0;
	while (j < cub->walltop_pixel)
	{
		cub->addr[(W_WIDTH * j) + cub->i] = (cub->clg.r << 16) \
			+ (cub->clg.g << 8) + (cub->clg.b);
		j++;
	}
}

void	draw_floor(t_struct *cub)
{
	int	n;

	n = cub->wallbottom_pixel;
	while (n < W_HEIGHT)
	{
		cub->addr[(W_WIDTH * n) + cub->i] = \
			(cub->flr.r << 16) + (cub->flr.g << 8) + (cub->flr.b);
		n++;
	}
}

void	check_vert_texture(t_struct	*cub)
{
	if (cub->ray.rayangle < (M_PI / 2) || \
				cub->ray.rayangle > ((3 * M_PI) / 2))
				cub->texturecolor = cub->texture[0].data[\
				(int)(cub->texture[0].img_width * \
					cub->textureoffsety) + (int)cub->textureoffsetx];
	else
		cub->texturecolor = cub->texture[1].data[\
			(int)(cub->texture[1].img_width * \
			cub->textureoffsety) + (int)cub->textureoffsetx];
}

void	check_hori_texture(t_struct	*cub)
{
	if (cub->ray.rayangle > 0 && cub->ray.rayangle < M_PI)
				cub->texturecolor = cub->texture[3].data[\
					(int)(cub->texture[3].img_width * \
						cub->textureoffsety) + (int)cub->textureoffsetx];
	else
		cub->texturecolor = cub->texture[2].data[\
			(int)(cub->texture[2].img_width * \
				cub->textureoffsety) + (int)cub->textureoffsetx];
}
