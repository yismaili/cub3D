/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 20:08:09 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	cast_hrzntal_rays(t_struct *cub)
{
	cub->tmp.y_hrzntlIntrsctn = floor(cub->player.position_y / \
			cub->scaleHeight) * cub->scaleHeight;
	if (cub->ray.rayFacingDown)
		cub->tmp.y_hrzntlIntrsctn += cub->scaleHeight;
	cub->tmp.x_hrzntlIntrsctn = cub->player.position_x + \
	(cub->tmp.y_hrzntlIntrsctn - cub->player.position_y) / \
	tan(cub->ray.rayAngle);
	cub->tmp.y_incrmnt = cub->scaleHeight;
	if (cub->ray.rayFacingUp)
		cub->tmp.y_incrmnt *= -1;
	if (cub->ray.rayFacingUp)
		cub->tmp.y_hrzntlIntrsctn -= 1;
	cub->tmp.x_incrmnt = cub->tmp.y_incrmnt / (tan(cub->ray.rayAngle));
	if (cub->ray.rayFacingLeft && cub->tmp.x_incrmnt > 0)
		cub->tmp.x_incrmnt *= -1;
	if (cub->ray.rayFacingRight && cub->tmp.x_incrmnt < 0)
		cub->tmp.x_incrmnt *= -1;
	searchto_wall_hrzntl(cub);
}

void	searchto_wall_hrzntl(t_struct *cub)
{
	bool	check;

	check = false;
	while (cub->tmp.x_hrzntlIntrsctn >= 0 && cub->tmp.x_hrzntlIntrsctn < \
			cub->widthofmap && cub->tmp.y_hrzntlIntrsctn >= 0 \
			&&cub->tmp.y_hrzntlIntrsctn < cub->heightofmap)
	{
		if (check_wall(cub, cub->tmp.x_hrzntlIntrsctn, \
					cub->tmp.y_hrzntlIntrsctn))
		{
			if (cub->ray.rayFacingUp)
				cub->tmp.y_hrzntlIntrsctn += 1;
			cub->ray.horzWallHitY = cub->tmp.y_hrzntlIntrsctn;
			cub->ray.horzWallHitX = cub->tmp.x_hrzntlIntrsctn;
			check = true;
			break ;
		}
		cub->tmp.x_hrzntlIntrsctn += cub->tmp.x_incrmnt;
		cub->tmp.y_hrzntlIntrsctn += cub->tmp.y_incrmnt;
	}
	if (!check)
	{
		cub->ray.horzWallHitX = 1e9;
		cub->ray.horzWallHitY = 1e9;
	}
}

void	cast_vrtcal_rays(t_struct *cub)
{
	cub->tmp.x_vrticlIntrsctn = floor(cub->player.position_x / \
			cub->scaleWidth) * cub->scaleWidth;
	if (cub->ray.rayFacingRight)
		cub->tmp.x_vrticlIntrsctn += cub->scaleWidth;
	cub->tmp.y_vrtclIntrsctn = cub->player.position_y + \
		((cub->tmp.x_vrticlIntrsctn - cub->player.position_x) * \
		tan(cub->ray.rayAngle));
	cub->tmp.x_incrmntVrtcl = cub->scaleWidth;
	if (cub->ray.rayFacingLeft)
		cub->tmp.x_incrmntVrtcl *= -1;
	if (cub->ray.rayFacingLeft)
		cub->tmp.x_vrticlIntrsctn -= 1;
	cub->tmp.y_incrmntVrtcl = cub->tmp.x_incrmntVrtcl * tan(cub->ray.rayAngle);
	if (cub->ray.rayFacingUp && cub->tmp.y_incrmntVrtcl > 0)
		cub->tmp.y_incrmntVrtcl *= -1;
	if (cub->ray.rayFacingDown && cub->tmp.y_incrmntVrtcl < 0)
		cub->tmp.y_incrmntVrtcl *= -1;
	searchto_wall_vrtcl(cub);
}

void	searchto_wall_vrtcl(t_struct *cub)
{
	bool	check;

	check = false;
	while (cub->tmp.x_vrticlIntrsctn >= 0 && cub->tmp.x_vrticlIntrsctn < \
			cub->widthofmap && cub->tmp.y_vrtclIntrsctn >= 0 && \
			cub->tmp.y_vrtclIntrsctn < cub->heightofmap)
	{
		if (check_wall(cub, cub->tmp.x_vrticlIntrsctn, \
					cub->tmp.y_vrtclIntrsctn))
		{
			if (cub->ray.rayFacingLeft)
				cub->tmp.x_vrticlIntrsctn += 1;
			cub->ray.vrticlWallHitX = cub->tmp.x_vrticlIntrsctn;
			cub->ray.vrtclWallHitY = cub->tmp.y_vrtclIntrsctn;
			check = true;
			break ;
		}
		cub->tmp.x_vrticlIntrsctn += cub->tmp.x_incrmntVrtcl;
		cub->tmp.y_vrtclIntrsctn += cub->tmp.y_incrmntVrtcl;
	}
	if (!cub->tmp.check)
	{
		cub->ray.vrticlWallHitX = 1e9;
		cub->ray.vrtclWallHitY = 1e9;
	}
}

void	cast_all_rays(t_struct *cub)
{	
	double	hrzntl_dstnc;
	double	vrtcl_dstnc;

	init_dataray(cub);
	cast_vrtcal_rays(cub);
	cast_hrzntal_rays(cub);
	hrzntl_dstnc = calcul_distance(cub->ray.horzWallHitX, \
	cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
	vrtcl_dstnc = calcul_distance(cub->ray.vrticlWallHitX, \
	cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
	if (hrzntl_dstnc >= vrtcl_dstnc)
	{
		cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
		cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
		cub->ray.Distance = vrtcl_dstnc;
		cub->ray.check = 1;
	}
	else
	{
		cub->ray.wallHit_x = cub->ray.horzWallHitX;
		cub->ray.wallHit_y = cub->ray.horzWallHitY;
		cub->ray.Distance = hrzntl_dstnc;
		cub->ray.check = 2;
	}
}
