/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:47:10 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/21 19:53:04 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void drawRaysOfplyer_mini(t_struct *cub, int x, int y, int color)
{
    int i = 0;
    double angleIncrem = (M_PI / 3) / cub->numOfRays;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6);  
    while (i < cub->numOfRays)
    {  
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        castAllRays_mini(cub);
        ddaForLine(cub, x, y, cub->ray.wallHit_x , cub->ray.wallHit_y ,color);
        cub->ray.rayAngle += angleIncrem;
        i++;
   } 
}

void castHrzntalRays_mini(t_struct *cub)
{
    double x_hrzntlIntrsctn;
    double y_hrzntlIntrsctn;
    double y_incrmnt;
    double x_incrmnt;
    
    y_hrzntlIntrsctn =  floor(cub->mini_map.mini_y / cub->mini_map.mini_scaleHeight) * cub->mini_map.mini_scaleHeight;
    if (cub->ray.rayFacingDown)
        y_hrzntlIntrsctn += cub->mini_map.mini_scaleHeight;
    x_hrzntlIntrsctn = cub->mini_map.mini_x + (y_hrzntlIntrsctn - cub->mini_map.mini_y) / tan(cub->ray.rayAngle);
    y_incrmnt = cub->mini_map.mini_scaleHeight;
    if (cub->ray.rayFacingUp)
        y_incrmnt *= -1;
    if (cub->ray.rayFacingUp)
        y_hrzntlIntrsctn -= 1;
    x_incrmnt =  y_incrmnt / (tan(cub->ray.rayAngle));
    if (cub->ray.rayFacingLeft && x_incrmnt > 0)
        x_incrmnt *= -1;
    if (cub->ray.rayFacingRight && x_incrmnt < 0)
        x_incrmnt *= -1;
    bool check = false;
    while (x_hrzntlIntrsctn >= 0 && x_hrzntlIntrsctn < (W_WIDTH / 3) && y_hrzntlIntrsctn >= 0 &&y_hrzntlIntrsctn < (W_HEIGHT / 3))
    {
        if (check_wall_mini(cub, x_hrzntlIntrsctn,y_hrzntlIntrsctn))
        {
            cub->ray.horzWallHitX = x_hrzntlIntrsctn;
            cub->ray.horzWallHitY =y_hrzntlIntrsctn;
            check = true;
            break;
        }
        x_hrzntlIntrsctn += x_incrmnt;
        y_hrzntlIntrsctn += y_incrmnt;
     }
     if (!check)
     {
        cub->ray.horzWallHitX = 1e9;
        cub->ray.horzWallHitY = 1e9;
     }
}

void castVrtcalRays_mini(t_struct *cub)
{
    double y_vrtclIntrsctn;
    double x_vrticlIntrsctn;
    double x_incrmntVrtcl;
    double y_incrmntVrtcl;
    
    x_vrticlIntrsctn =  floor(cub->mini_map.mini_x / cub->mini_map.mini_scaleWidth) * cub->mini_map.mini_scaleWidth;
    if (cub->ray.rayFacingRight)
        x_vrticlIntrsctn += cub->mini_map.mini_scaleWidth;
    y_vrtclIntrsctn = cub->mini_map.mini_y + ((x_vrticlIntrsctn - cub->mini_map.mini_x) * tan(cub->ray.rayAngle));
    x_incrmntVrtcl = cub->mini_map.mini_scaleWidth;
    if (cub->ray.rayFacingLeft)
        x_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingLeft)
        x_vrticlIntrsctn -= 1;
    y_incrmntVrtcl =  x_incrmntVrtcl  * tan(cub->ray.rayAngle);
    if (cub->ray.rayFacingUp && y_incrmntVrtcl > 0)
        y_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingDown && y_incrmntVrtcl < 0)
        y_incrmntVrtcl *= -1;
    bool check = false;
    while (x_vrticlIntrsctn >= 0 && x_vrticlIntrsctn < (W_WIDTH / 3) && y_vrtclIntrsctn >= 0 && y_vrtclIntrsctn < (W_HEIGHT / 3))
    {
        if (check_wall_mini(cub, x_vrticlIntrsctn, y_vrtclIntrsctn))
        {
            cub->ray.vrticlWallHitX = x_vrticlIntrsctn;
            cub->ray.vrtclWallHitY = y_vrtclIntrsctn;
            check = true;
            break;
        }
        x_vrticlIntrsctn += x_incrmntVrtcl;
        y_vrtclIntrsctn += y_incrmntVrtcl;
     }
     if (!check)
     {
        cub->ray.vrticlWallHitX = 1e9;
        cub->ray.vrtclWallHitY = 1e9;
     }
}

void castAllRays_mini(t_struct *cub)
{
    double hrzntlDstnc = 0;
    double vrtclDstnc = 0;

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
    if (cub->ray.rayAngle < (M_PI/2) || cub->ray.rayAngle > ((3 * M_PI)/2))
        cub->ray.rayFacingRight = 1;
    else
        cub->ray.rayFacingLeft = 1;
    castVrtcalRays_mini(cub);
    castHrzntalRays_mini(cub);
    if (cub->ray.vrtclWallHitY != 1e9 && cub->ray.vrticlWallHitX != 1e9)
        hrzntlDstnc = calculDistance(cub->ray.horzWallHitX, cub->ray.horzWallHitY, cub->mini_map.mini_x, cub->mini_map.mini_y);
    if (cub->ray.horzWallHitX != 1e9 && cub->ray.horzWallHitY != 1e9)
        vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX, cub->ray.vrtclWallHitY, cub->mini_map.mini_x, cub->mini_map.mini_y);
    if (hrzntlDstnc >= vrtclDstnc)
    {
        cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
        cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
    }
    else
    {
        cub->ray.wallHit_x = cub->ray.horzWallHitX;
        cub->ray.wallHit_y = cub->ray.horzWallHitY;
    }
}

int check_wall_mini(t_struct *cub, double x, double y)
 {
    char **map;
    map = ft_jump_lines(cub);
    int gred_y = (int)(y/cub->mini_map.mini_scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->mini_map.mini_scaleWidth);
    if (!map[gred_y])
        return (1);
    if ( map[gred_y][gred_x] == '1')
        return (1);
    return (0);
 }

 void check_nextSteep_mini(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->mini_map.mini_x + (cos(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 1.5));
    new_y = cub->mini_map.mini_y + (sin(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 1.5));
    if (check_wall_mini(cub, new_x, new_y) != 1)
    {
        cub->mini_map.mini_x = new_x;
        cub->mini_map.mini_y = new_y;
    }   
}

void check_downSteep_mini(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->mini_map.mini_x + (cos(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 1.5));
    new_y = cub->mini_map.mini_y + (sin(cub->player.rottAngle + (M_PI/2)) * ((double)cub->player.walkDown * 1.5));
    if (check_wall_mini(cub, new_x, new_y) != 1)
    {
        cub->mini_map.mini_x = new_x;
        cub->mini_map.mini_y = new_y;
    }   
}