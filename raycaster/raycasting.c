/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 23:23:00 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	cast_hrzntal_rays(t_struct *cub)
{
	cub->tmp.y_hrzntlintrsctn = floor(cub->player.position_y / \
			cub->scaleheight) * cub->scaleheight;
	if (cub->ray.rayfacingdown)
		cub->tmp.y_hrzntlintrsctn += cub->scaleheight;
	cub->tmp.x_hrzntlintrsctn = cub->player.position_x + \
	(cub->tmp.y_hrzntlintrsctn - cub->player.position_y) / \
	tan(cub->ray.rayangle);
	cub->tmp.y_incrmnt = cub->scaleheight;
	if (cub->ray.rayfacingup)
		cub->tmp.y_incrmnt *= -1;
	if (cub->ray.rayfacingup)
		cub->tmp.y_hrzntlintrsctn -= 1;
	cub->tmp.x_incrmnt = cub->tmp.y_incrmnt / (tan(cub->ray.rayangle));
	if (cub->ray.rayfacingleft && cub->tmp.x_incrmnt > 0)
		cub->tmp.x_incrmnt *= -1;
	if (cub->ray.rayfacingright && cub->tmp.x_incrmnt < 0)
		cub->tmp.x_incrmnt *= -1;
	searchto_wall_hrzntl(cub);
}

void	searchto_wall_hrzntl(t_struct *cub)
{
	bool	check;

	check = false;
	while (cub->tmp.x_hrzntlintrsctn >= 0 && cub->tmp.x_hrzntlintrsctn < \
			cub->widthofmap && cub->tmp.y_hrzntlintrsctn >= 0 \
			&&cub->tmp.y_hrzntlintrsctn < cub->heightofmap)
	{
		if (check_wall(cub, cub->tmp.x_hrzntlintrsctn, \
					cub->tmp.y_hrzntlintrsctn))
		{
			if (cub->ray.rayfacingup)
				cub->tmp.y_hrzntlintrsctn += 1;
			cub->ray.horzwallhity = cub->tmp.y_hrzntlintrsctn;
			cub->ray.horzwallhitx = cub->tmp.x_hrzntlintrsctn;
			check = true;
			break ;
		}
		cub->tmp.x_hrzntlintrsctn += cub->tmp.x_incrmnt;
		cub->tmp.y_hrzntlintrsctn += cub->tmp.y_incrmnt;
	}
	if (!check)
	{
		cub->ray.horzwallhitx = 1e9;
		cub->ray.horzwallhity = 1e9;
	}
}

void	cast_vrtcal_rays(t_struct *cub)
{
	cub->tmp.x_vrticlintrsctn = floor(cub->player.position_x / \
			cub->scalewidth) * cub->scalewidth;
	if (cub->ray.rayfacingright)
		cub->tmp.x_vrticlintrsctn += cub->scalewidth;
	cub->tmp.y_vrtclintrsctn = cub->player.position_y + \
		((cub->tmp.x_vrticlintrsctn - cub->player.position_x) * \
		tan(cub->ray.rayangle));
	cub->tmp.x_incrmntvrtcl = cub->scalewidth;
	if (cub->ray.rayfacingleft)
		cub->tmp.x_incrmntvrtcl *= -1;
	if (cub->ray.rayfacingleft)
		cub->tmp.x_vrticlintrsctn -= 1;
	cub->tmp.y_incrmntvrtcl = cub->tmp.x_incrmntvrtcl * tan(cub->ray.rayangle);
	if (cub->ray.rayfacingup && cub->tmp.y_incrmntvrtcl > 0)
		cub->tmp.y_incrmntvrtcl *= -1;
	if (cub->ray.rayfacingdown && cub->tmp.y_incrmntvrtcl < 0)
		cub->tmp.y_incrmntvrtcl *= -1;
	searchto_wall_vrtcl(cub);
}

void	searchto_wall_vrtcl(t_struct *cub)
{
	bool	check;

	check = false;
	while (cub->tmp.x_vrticlintrsctn >= 0 && cub->tmp.x_vrticlintrsctn < \
			cub->widthofmap && cub->tmp.y_vrtclintrsctn >= 0 && \
			cub->tmp.y_vrtclintrsctn < cub->heightofmap)
	{
		if (check_wall(cub, cub->tmp.x_vrticlintrsctn, \
					cub->tmp.y_vrtclintrsctn))
		{
			if (cub->ray.rayfacingleft)
				cub->tmp.x_vrticlintrsctn += 1;
			cub->ray.vrticlwallhitx = cub->tmp.x_vrticlintrsctn;
			cub->ray.vrtclwallhity = cub->tmp.y_vrtclintrsctn;
			check = true;
			break ;
		}
		cub->tmp.x_vrticlintrsctn += cub->tmp.x_incrmntvrtcl;
		cub->tmp.y_vrtclintrsctn += cub->tmp.y_incrmntvrtcl;
	}
	if (!cub->tmp.check)
	{
		cub->ray.vrticlwallhitx = 1e9;
		cub->ray.vrtclwallhity = 1e9;
	}
}

void	cast_all_rays(t_struct *cub)
{	
	double	hrzntl_dstnc;
	double	vrtcl_dstnc;

	init_dataray(cub);
	cast_vrtcal_rays(cub);
	cast_hrzntal_rays(cub);
	hrzntl_dstnc = calcul_distance(cub->ray.horzwallhitx, \
	cub->ray.horzwallhity, cub->player.position_x, cub->player.position_y);
	vrtcl_dstnc = calcul_distance(cub->ray.vrticlwallhitx, \
	cub->ray.vrtclwallhity, cub->player.position_x, cub->player.position_y);
	if (hrzntl_dstnc >= vrtcl_dstnc)
	{
		cub->ray.wallhit_x = cub->ray.vrticlwallhitx;
		cub->ray.wallhit_y = cub->ray.vrtclwallhity;
		cub->ray.distance = vrtcl_dstnc;
		cub->ray.check = 1;
	}
	else
	{
		cub->ray.wallhit_x = cub->ray.horzwallhitx;
		cub->ray.wallhit_y = cub->ray.horzwallhity;
		cub->ray.distance = hrzntl_dstnc;
		cub->ray.check = 2;
	}
}
