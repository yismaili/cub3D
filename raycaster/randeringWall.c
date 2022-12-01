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

void	calcule_wall_strip_height(t_struct	*cub)
{
	double	correctdistance;

	correctdistance = cub->ray.distance * \
		cos(cub->ray.rayangle - cub->player.rottangle);
	cub->wallstripheight = (cub->scaleheight * (W_HEIGHT)) / correctdistance;
	cub->len = cub->wallstripheight;
	if (cub->wallstripheight > W_HEIGHT)
		cub->wallstripheight = W_HEIGHT;
		cub->walltop_pixel = (W_HEIGHT / 2) - (cub->wallstripheight / 2);
	if (cub->walltop_pixel < 0)
		cub->walltop_pixel = 0;
	cub->wallbottom_pixel = (W_HEIGHT / 2) + (cub->wallstripheight / 2);
	if (cub->wallbottom_pixel >= W_HEIGHT)
		cub->wallbottom_pixel = W_HEIGHT - 1;
}

void	draw_the_wall(t_struct	*cub)
{
	int	o;
	int	distancefromtop;

	o = cub->walltop_pixel;
	while (o < cub->wallbottom_pixel)
	{
		distancefromtop = o + ((cub->len / 2) - (W_HEIGHT / 2));
		if (distancefromtop < 0)
			distancefromtop = 0;
		cub->textureoffsety = (distancefromtop) * \
			((double)cub->texture_height / cub->len);
		cub->textureoffsety = floor(cub->textureoffsety);
		cub->texturecolor = 0;
		if (cub->ray.check == 1)
			check_vert_texture(cub);
		else if (cub->ray.check == 2)
			check_hori_texture(cub);
		cub->addr[(W_WIDTH * o) + cub->i] = cub->texturecolor;
		o++;
	}
}

void	randering_wall(t_struct	*cub)
{
	int		j;
	double	angleincrem;

	cub->i = -1;
	cub->wallstripheight = 0;
	angleincrem = (M_PI / 3) / cub->numofrays;
	cub->ray.rayangle = cub->player.rottangle - (M_PI / 6);
	j = 0;
	while (++cub->i < cub->numofrays)
	{
		cub->ray.rayangle = normalize_angle(cub->ray.rayangle);
		cast_all_rays(cub);
		calcule_wall_strip_height(cub);
		calcule_xoffset(cub);
		draw_ceilling(cub);
		draw_the_wall(cub);
		draw_floor(cub);
		cub->ray.rayangle += angleincrem;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}
