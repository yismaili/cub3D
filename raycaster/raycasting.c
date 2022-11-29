/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 18:55:13 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* cast all rays */

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
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
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
void drawRaysOfplyer_mini(t_struct *cub, int x, int y, int color)
{
    int i = 0;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6);  
    while (i < cub->numOfRays)
    {  
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        cast_all_rays(cub);
        cub->ray.wallHit_x = (cub->ray.wallHit_x / cub->scaleWidth) * cub->mini_map.mini_scaleWidth;
        cub->ray.wallHit_y = (cub->ray.wallHit_y / cub->scaleHeight) * cub->mini_map.mini_scaleHeight;
        dda(cub, x, y, cub->ray.wallHit_x , cub->ray.wallHit_y ,color);
        cub->ray.rayAngle += cub->angleIncrem;
        i++;
   } 
}

int abs(int n) 
{ 
    if (n > 0){
        return (n);
    }
    else {
        return (n *(-1));
    }
}

void dda(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    int dstnc_x;
    int dstnc_y;
    int steps;
    float x_inc;
    int     i;
    float y_inc;
    float x;
    float y;
    
    dstnc_x = x_1 - x_0;
    dstnc_y = y_1 - y_0;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    x_inc = dstnc_x / (float)steps;
    y_inc = dstnc_y / (float)steps;
    x = x_0;
    y = y_0;
    i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; 
       y += y_inc;
       i++;
    }
}
 
 int check_wall(t_struct *cub, double x, double y)
 {
    int gred_y;
    int gred_x;
    
    gred_y = (int)(y / cub->scaleHeight);
    gred_x = (int)(x / cub->scaleWidth);
    if (gred_y < cub->heightof_minimap  && gred_x <  cub->widthof_minimap)
    {
        if (cub->my_map[gred_y][gred_x] == '1')
            return (1);   
    }
    return (0);
 }

 double normalizeAngle(double angle)
 {
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle == M_PI || angle == 0)
        angle += 0.000000000001;
    return (angle);
 }
 

double calculDistance(double wallHit_x, double wallHit_y, double x, double y)
{
    return (sqrt(pow((x - wallHit_x ),2) + pow((y - wallHit_y),2)));  
}
    
void cast_hrzntal_rays(t_struct *cub)
{
    cub->tmp.y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (cub->ray.rayFacingDown)
        cub->tmp.y_hrzntlIntrsctn += cub->scaleHeight;
    cub->tmp.x_hrzntlIntrsctn = cub->player.position_x + (cub->tmp.y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
    cub->tmp.y_incrmnt = cub->scaleHeight;
    if (cub->ray.rayFacingUp)
        cub->tmp.y_incrmnt *= -1;
    if (cub->ray.rayFacingUp)
        cub->tmp.y_hrzntlIntrsctn -= 1;
    cub->tmp.x_incrmnt =  cub->tmp.y_incrmnt / (tan(cub->ray.rayAngle));
    if (cub->ray.rayFacingLeft && cub->tmp.x_incrmnt > 0)
        cub->tmp.x_incrmnt *= -1;
    if (cub->ray.rayFacingRight && cub->tmp.x_incrmnt < 0)
        cub->tmp.x_incrmnt *= -1;
    searchto_wall_hrzntl(cub);
}

void    searchto_wall_hrzntl(t_struct *cub)
{
    bool check;

    check = false;
    while (cub->tmp.x_hrzntlIntrsctn >= 0 && cub->tmp.x_hrzntlIntrsctn < cub->widthofmap && cub->tmp.y_hrzntlIntrsctn >= 0 &&cub->tmp.y_hrzntlIntrsctn < cub->heightofmap)
    {
        if (check_wall(cub, cub->tmp.x_hrzntlIntrsctn,cub->tmp.y_hrzntlIntrsctn))
        {
            if (cub->ray.rayFacingUp)
                cub->tmp.y_hrzntlIntrsctn += 1;
            cub->ray.horzWallHitY = cub->tmp.y_hrzntlIntrsctn;
            cub->ray.horzWallHitX = cub->tmp.x_hrzntlIntrsctn;
            check = true;
            break;
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

void cast_vrtcal_rays(t_struct *cub)
{
    cub->tmp.x_vrticlIntrsctn =  floor(cub->player.position_x / cub->scaleWidth) * cub->scaleWidth;
    if (cub->ray.rayFacingRight)
        cub->tmp.x_vrticlIntrsctn += cub->scaleWidth;
    cub->tmp.y_vrtclIntrsctn = cub->player.position_y + ((cub->tmp.x_vrticlIntrsctn - cub->player.position_x) * tan(cub->ray.rayAngle));
    cub->tmp.x_incrmntVrtcl = cub->scaleWidth;
    if (cub->ray.rayFacingLeft)
        cub->tmp.x_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingLeft)
        cub->tmp.x_vrticlIntrsctn -= 1;
    cub->tmp.y_incrmntVrtcl =  cub->tmp.x_incrmntVrtcl  * tan(cub->ray.rayAngle);
    if (cub->ray.rayFacingUp && cub->tmp.y_incrmntVrtcl > 0)
        cub->tmp.y_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingDown && cub->tmp.y_incrmntVrtcl < 0)
        cub->tmp.y_incrmntVrtcl *= -1;
    searchto_wall_vrtcl(cub);
}

void    searchto_wall_vrtcl(t_struct *cub)
{
    bool check;
    check = false;
    while (cub->tmp.x_vrticlIntrsctn >= 0 && cub->tmp.x_vrticlIntrsctn < cub->widthofmap && cub->tmp.y_vrtclIntrsctn >= 0 && cub->tmp.y_vrtclIntrsctn <  cub->heightofmap)
    {
        if (check_wall(cub, cub->tmp.x_vrticlIntrsctn, cub->tmp.y_vrtclIntrsctn))
        {
            if (cub->ray.rayFacingLeft)
                 cub->tmp.x_vrticlIntrsctn += 1;
            cub->ray.vrticlWallHitX = cub->tmp.x_vrticlIntrsctn;
            cub->ray.vrtclWallHitY = cub->tmp.y_vrtclIntrsctn;
            check = true;
            break;
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

void cast_all_rays(t_struct *cub)
{
    double hrzntlDstnc = 0;
    double vrtclDstnc = 0;

    init_dataray(cub);
    cast_vrtcal_rays(cub);
    cast_hrzntal_rays(cub);
    hrzntlDstnc = calculDistance(cub->ray.horzWallHitX, cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
    vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX, cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
    if (hrzntlDstnc >= vrtclDstnc)
    {
        cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
        cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
        cub->ray.Distance  = vrtclDstnc;
        cub->ray.check = 1;
    }
    else
    {
        cub->ray.wallHit_x = cub->ray.horzWallHitX;
        cub->ray.wallHit_y = cub->ray.horzWallHitY;
        cub->ray.Distance  = hrzntlDstnc;
        cub->ray.check = 2;
    }
}

void    init_dataray(t_struct *cub)
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