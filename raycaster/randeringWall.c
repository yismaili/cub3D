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
	cub->ray.wallhit_x = 0;
	cub->ray.wallhit_y = 0;
	cub->ray.distance = 0;
	cub->ray.rayfacingdown = 0;
	cub->ray.rayfacingup = 0;
	cub->ray.rayfacingright = 0;
	cub->ray.rayfacingleft = 0;
	cub->ray.vrticlwallhitx = 0;
	cub->ray.vrtclwallhity = 0;
	cub->ray.horzwallhitx = 0;
	cub->ray.horzwallhity = 0;
	if (cub->ray.rayangle > 0 && cub->ray.rayangle < M_PI)
		cub->ray.rayfacingdown = 1;
	else
		cub->ray.rayfacingup = 1;
	if (cub->ray.rayangle < (M_PI / 2) || cub->ray.rayangle > ((3 * M_PI) / 2))
		cub->ray.rayfacingright = 1;
	else
		cub->ray.rayfacingleft = 1;
}

void	randering_wall(t_struct *cub)
{
	cub->tmp.i_n = -1;
	cub->tmp.o = 0;
	cub->wallstripheight = 0;
	cub->ray.rayangle = cub->player.rottangle - (M_PI / 6);
	while (++cub->tmp.i_n < cub->numofrays)
	{
		cub->ray.rayangle = normalize_angle(cub->ray.rayangle);
		cast_all_rays(cub);
		calcul_heigtof_wall(cub);
		calcul_texture_pixls(cub);
		cub->tmp.n = cub->tmp.wallbottompixel;
		while (cub->tmp.n < W_HEIGHT)
		{
			cub->addr[(W_WIDTH * cub->tmp.n) + cub->tmp.i_n] = (cub->flr.r \
					<< 16) + (cub->flr.g << 8) + (cub->flr.b);
			cub->tmp.n++;
		}
		cub->ray.rayangle += cub->angleincrem;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}

void	calcul_heigtof_wall(t_struct *cub)
{
	cub->tmp.correctdistance = cub->ray.distance * cos(cub->ray.rayangle - \
			cub->player.rottangle);
	cub->wallstripheight = (cub->scaleheight * (W_HEIGHT)) \
						/ cub->tmp.correctdistance;
	cub->tmp.len_n = cub->wallstripheight;
	if (cub->wallstripheight > W_HEIGHT)
		cub->wallstripheight = W_HEIGHT;
	cub->tmp.walltoppixel = (W_HEIGHT / 2) - (cub->wallstripheight / 2);
	if (cub->tmp.walltoppixel < 0)
		cub->tmp.walltoppixel = 0;
	cub->tmp.wallbottompixel = (W_HEIGHT / 2) + (cub->wallstripheight / 2);
	if (cub->tmp.wallbottompixel >= W_HEIGHT)
		cub->tmp.wallbottompixel = W_HEIGHT -1;
	cub->tmp.o = (cub->tmp.walltoppixel -1);
	if (cub->ray.check == 1)
		cub->tmp.textureoffsetx = cub->ray.vrtclwallhity;
	else
		cub->tmp.textureoffsetx = cub->ray.horzwallhitx;
	cub->tmp.j_n = 0;
	while (cub->tmp.j_n < cub->tmp.walltoppixel)
	{
		cub->addr[(W_WIDTH * cub->tmp.j_n) + cub->tmp.i_n] = \
					(cub->clg.r << 16) + (cub->clg.g << 8) + (cub->clg.b);
		cub->tmp.j_n++;
	}
}
