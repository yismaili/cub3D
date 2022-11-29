/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randeringWall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:51:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 22:26:51 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_color_buffer(t_struct *cub)
{
	int	i;
	int	k;

	i = 0;
	while (i < W_HEIGHT)
	{
		k = 0;
		while (k < W_WIDTH)
		{
			cub->color_buffer[i][k] = 0;
			k++;
		}
		i++;
	}
	cub->check_test = 0;
}

void	init_dataray(t_struct *cub)
{
	cub->ray.wallHit_x = 0;
	cub->ray.wallHit_y = 0;
	cub->ray.Distance = 0;
	cub->ray.rayFacingDown = 0;
	cub->ray.rayFacingUp = 0;
	cub->ray.rayFacingRight = 0;
	cub->ray.rayFacingLeft = 0;
	cub->ray.vrticlWallHitX = 0;
	cub->ray.vrtclWallHitY = 0;
	cub->ray.horzWallHitX = 0;
	cub->ray.horzWallHitY = 0;
	if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
		cub->ray.rayFacingDown = 1;
	else
		cub->ray.rayFacingUp = 1;
	if (cub->ray.rayAngle < (M_PI / 2) || cub->ray.rayAngle > ((3 * M_PI) / 2))
		cub->ray.rayFacingRight = 1;
	else
		cub->ray.rayFacingLeft = 1;
}

void	randering_wall(t_struct *cub)
{
	cub->tmp.i_n = -1;
	cub->tmp.o = 0;
	cub->wallStripHeight = 0;
	cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6);
	while (++cub->tmp.i_n < cub->numOfRays)
	{
		cub->ray.rayAngle = normalize_angle(cub->ray.rayAngle);
		cast_all_rays(cub);
		calcul_heigtof_wall(cub);
		calcul_texture_pixls(cub);
		cub->tmp.n = cub->tmp.wallBottomPixel;
		while (cub->tmp.n < W_HEIGHT)
		{
			cub->addr[(W_WIDTH * cub->tmp.n) + cub->tmp.i_n] = (cub->flr.r \
					<< 16) + (cub->flr.g << 8) + (cub->flr.b);
			cub->tmp.n++;
		}
		cub->ray.rayAngle += cub->angleIncrem;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}

void	calcul_heigtof_wall(t_struct *cub)
{
	cub->tmp.correctDistance = cub->ray.Distance * cos(cub->ray.rayAngle - \
			cub->player.rottAngle);
	cub->wallStripHeight = (cub->scaleHeight * (W_HEIGHT)) \
						/ cub->tmp.correctDistance;
	cub->tmp.len_n = cub->wallStripHeight;
	if (cub->wallStripHeight > W_HEIGHT)
		cub->wallStripHeight = W_HEIGHT;
	cub->tmp.wallTopPixel = (W_HEIGHT / 2) - (cub->wallStripHeight / 2);
	if (cub->tmp.wallTopPixel < 0)
		cub->tmp.wallTopPixel = 0;
	cub->tmp.wallBottomPixel = (W_HEIGHT / 2) + (cub->wallStripHeight / 2);
	if (cub->tmp.wallBottomPixel >= W_HEIGHT)
		cub->tmp.wallBottomPixel = W_HEIGHT -1;
	cub->tmp.o = (cub->tmp.wallTopPixel -1);
	if (cub->ray.check == 1)
		cub->tmp.textureOffsetX = cub->ray.vrtclWallHitY;
	else
		cub->tmp.textureOffsetX = cub->ray.horzWallHitX;
	cub->tmp.j_n = 0;
	while (cub->tmp.j_n < cub->tmp.wallTopPixel)
	{
		cub->addr[(W_WIDTH * cub->tmp.j_n) + cub->tmp.i_n] = \
					(cub->clg.r << 16) + (cub->clg.g << 8) + (cub->clg.b);
		cub->tmp.j_n++;
	}
}
