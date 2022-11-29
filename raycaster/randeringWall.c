/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randeringWall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:51:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 20:07:01 by yismaili         ###   ########.fr       */
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

void randering_wall(t_struct *cub)
{
    int i = -1;
	int		wallBottomPixel ;
	double		wallTopPixel;
    int o;
    o = 0;
    cub->wallStripHeight = 0;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6); 
    while (++i < cub->numOfRays)
    { 
        cub->ray.rayAngle = normalize_angle(cub->ray.rayAngle);
        cast_all_rays(cub);
	    double correctDistance = cub->ray.Distance * cos(cub->ray.rayAngle - cub->player.rottAngle);
	    cub->wallStripHeight = (cub->scaleHeight * (W_HEIGHT)) /  correctDistance;
        double len = cub->wallStripHeight;
	    if (cub->wallStripHeight > W_HEIGHT)
		     cub->wallStripHeight = W_HEIGHT;
	    wallTopPixel = (W_HEIGHT/ 2) - ( cub->wallStripHeight/ 2);
	    if (wallTopPixel < 0)
		    wallTopPixel = 0;
	    wallBottomPixel = (W_HEIGHT / 2) + (cub->wallStripHeight / 2);
	    if (wallBottomPixel >= W_HEIGHT)
		    wallBottomPixel = W_HEIGHT - 1;
	    o = (wallTopPixel - 1);
        double textureOffsetX ;
        double textureOffsetY;
        if(cub->ray.check == 1)
        {
                textureOffsetX = cub->ray.vrtclWallHitY;
        }else{
                textureOffsetX = cub->ray.horzWallHitX;
        }

        int j = 0;
        while(j < wallTopPixel)
        {
            cub->addr[(W_WIDTH * j) + i] = (cub->clg.r << 16) + (cub->clg.g << 8) + (cub->clg.b);
            j++;
        }
        textureOffsetX /= cub->scaleHeight;
        textureOffsetX -= floor(textureOffsetX);
        textureOffsetX *= cub->texture->img_width;
        o = wallTopPixel;
        while (o < wallBottomPixel)
        {
            int distanceFromTop = o + ((len / 2) - (W_HEIGHT/2));
            if (distanceFromTop < 0)
                distanceFromTop = 0;

            textureOffsetY = (distanceFromTop) * ((double)cub->texture->img_height/ len);
            textureOffsetY = floor(textureOffsetY);

            unsigned int texturecolor = 0;
           
            if(cub->ray.check == 1)//vertical
           {
                if(cub->ray.rayAngle < (M_PI / 2) || cub->ray.rayAngle > ((3 * M_PI) / 2))
                    texturecolor = cub->texture[0].data[(int)(cub->texture[0].img_width * textureOffsetY) + (int)textureOffsetX];
                else
                    texturecolor = cub->texture[1].data[(int)(cub->texture[1].img_width * textureOffsetY) + (int)textureOffsetX];
 
            }
            else if(cub->ray.check  == 2)//horizontal
            {
                if(cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
                    texturecolor = cub->texture[3].data[(int)(cub->texture[3].img_width * textureOffsetY) + (int)textureOffsetX];
                else
                    texturecolor = cub->texture[2].data[(int)(cub->texture[2].img_width * textureOffsetY) + (int)textureOffsetX];
                
           }

            cub->addr[(W_WIDTH * o) + i] = texturecolor;
            cub->check_test = 1;
            o++;
        }
        int n = wallBottomPixel;
        while(n < W_HEIGHT)
        {
            cub->addr[(W_WIDTH * n) + i] = (cub->flr.r << 16) + (cub->flr.g << 8) + (cub->flr.b);
            n++;
        }
        cub->ray.rayAngle += cub->angleIncrem;
    }
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
} 
