/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/20 20:27:01 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* cast all rays */
void draw_player(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
	x_1 = x + cos(cub->player.rottAngle) * 42;
    y_1 = y + sin(cub->player.rottAngle) * 42;
    ddaForLine(cub, x, y, x_1, y_1, color);  
}

void drawRaysOfplyer(t_struct *cub, int x, int y, int color)
{
    int i = 0;
    double angleIncrem = (M_PI / 3) / cub->numOfRays;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6);  
    while (i < cub->numOfRays)
    {  
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        castAllRays(cub);
        ddaForLine(cub, x, y, cub->ray.wallHit_x, cub->ray.wallHit_y,color);
        cub->ray.rayAngle += angleIncrem;
        i++;
   } 
}

// Function for finding absolute value
int abs(int n) 
{ 
    if (n > 0){
        return (n);
    }
    else {
        return (n *(-1));
    }
}
// DDA Function for line generation
void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    // calculate dstnc_x & dstnc_y
    int dstnc_x = x_1 - x_0;
    int dstnc_y = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    // calculate increment in x & y for each steps
    float x_inc = dstnc_x / (float)steps;
    float y_inc = dstnc_y / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; // increment in x at each step
       y += y_inc; // increment in y at each step
       i++;
    }
}
 
 int check_wall(t_struct *cub, double x, double y)
 {
    char **map;
    map = ft_jump_lines(cub);
    int gred_y = (int)(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->scaleWidth);
    if (!map[gred_y])
        return (1);
    if ( map[gred_y][gred_x] == '1' ||  !map[gred_y])
        return (1);
    return (0);
 }

 double normalizeAngle(double angle)
 {
    // if (angle > 0)
    //     angle = fmod(angle, 2 * M_PI);
    // else
    //     angle += 2*M_PI;
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle == M_PI || angle == 0)
        angle += 0.000000000001;
    return (angle);
 }
 

double calculDistance(double wallHit_x, double wallHit_y, double x, double y)
{
    return (sqrt(pow((x - wallHit_x ),2) + pow((y- wallHit_y),2)));  
}
    
void castHrzntalRays(t_struct *cub)
{
    double x_hrzntlIntrsctn;
    double y_hrzntlIntrsctn;
    double y_incrmnt;
    double x_incrmnt;
    double x_nextHrzntal;
    double y_nextHrzntal;

    cub->ray.horzWallHitX = cub->player.position_x;
    cub->ray.horzWallHitY = cub->player.position_y;
    cub->ray.foundHorzWallHit = 0;
    y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (cub->ray.rayFacingDown)
        y_hrzntlIntrsctn += cub->scaleHeight;
    x_hrzntlIntrsctn = cub->player.position_x + (y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
    //    printf("%f\n",x_hrzntlIntrsctn);
    y_incrmnt = cub->scaleHeight;
    if (cub->ray.rayFacingUp)
        y_incrmnt *= -1;
    if (cub->ray.rayFacingUp)
        y_hrzntlIntrsctn -= 1;
    x_incrmnt =  y_incrmnt / (tan(cub->ray.rayAngle));
    if (cub->ray.rayFacingLeft && x_incrmnt > 0)
        x_incrmnt *= -1;
    if (cub->ray.rayFacingRight && x_incrmnt < 0)
        x_incrmnt *= -1;
    x_nextHrzntal = x_hrzntlIntrsctn;
    y_nextHrzntal = y_hrzntlIntrsctn;
    bool check = false;
    while (x_nextHrzntal >= 0 && x_nextHrzntal < W_WIDTH && y_nextHrzntal >= 0 && y_nextHrzntal < W_HEIGHT )
    {
        if (check_wall(cub, x_nextHrzntal, y_nextHrzntal))
        {
            // printf("hrzntal x ---> %f\n", x_nextHrzntal);
            //  printf("hrzntal x ---> %f\n", y_nextHrzntal);
            cub->ray.horzWallHitX = x_nextHrzntal;
            cub->ray.horzWallHitY = y_nextHrzntal;
            check = true;
            break;
        }
        x_nextHrzntal += x_incrmnt;
        y_nextHrzntal += y_incrmnt;
     }
     if (!check)
     {
        cub->ray.horzWallHitX = 1e9;
        cub->ray.horzWallHitY = 1e9;
     }
}

void castVrtcalRays(t_struct *cub)
{
    double y_vrtclIntrsctn;
    double x_vrticlIntrsctn;
    double x_incrmntVrtcl;
    double y_incrmntVrtcl;
    double x_nextVrtcl;
    double y_nextVrtcl;
     
    cub->ray.vrticlWallHitX = 0;
    cub->ray.vrtclWallHitY = 0;
    cub->ray.foundvrtclWallHit = 0;
    x_vrticlIntrsctn =  floor(cub->player.position_x / cub->scaleWidth) * cub->scaleWidth;
    if (cub->ray.rayFacingRight)
        x_vrticlIntrsctn += cub->scaleWidth;
    y_vrtclIntrsctn = cub->player.position_y + ((x_vrticlIntrsctn - cub->player.position_x) * tan(cub->ray.rayAngle));
      //printf("%f\n",y_vrtclIntrsctn);
    x_incrmntVrtcl = cub->scaleWidth;
    if (cub->ray.rayFacingLeft)
        x_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingLeft)
        x_vrticlIntrsctn -= 1;
    y_incrmntVrtcl =  x_incrmntVrtcl  * tan(cub->ray.rayAngle);
    if (cub->ray.rayFacingUp && y_incrmntVrtcl > 0)
        y_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingDown && y_incrmntVrtcl < 0)
        y_incrmntVrtcl *= -1;
    x_nextVrtcl = x_vrticlIntrsctn;
    y_nextVrtcl = y_vrtclIntrsctn;
    bool check = false;
    while (x_nextVrtcl >= 0 && x_nextVrtcl < W_WIDTH && y_nextVrtcl >= 0 && y_nextVrtcl < W_HEIGHT)
    {
        if (check_wall(cub, x_nextVrtcl, y_nextVrtcl))
        {
            cub->ray.vrticlWallHitX = x_nextVrtcl;
            cub->ray.vrtclWallHitY = y_nextVrtcl;
            check = true;
            break;
        }
        x_nextVrtcl += x_incrmntVrtcl;
        y_nextVrtcl += y_incrmntVrtcl;
     }
     if (!check)
     {
        cub->ray.vrticlWallHitX = 1e9;
        cub->ray.vrtclWallHitY = 1e9;
     }
}

void castAllRays(t_struct *cub)
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
    if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
        cub->ray.rayFacingDown = 1;
    else
        cub->ray.rayFacingUp = 1;
    if (cub->ray.rayAngle < (M_PI/2) || cub->ray.rayAngle > ((3 * M_PI)/2))
        cub->ray.rayFacingRight = 1;
    else
        cub->ray.rayFacingLeft = 1;
    castVrtcalRays(cub);
    castHrzntalRays(cub);
    if (cub->ray.vrtclWallHitY != 1e9 && cub->ray.vrticlWallHitX != 1e9)
        hrzntlDstnc = calculDistance(cub->ray.horzWallHitX, cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
    if (cub->ray.horzWallHitX != 1e9 && cub->ray.horzWallHitY != 1e9)
        vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX, cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
    // printf("vrtcal y >%f\n", cub->ray.vrtclWallHitY);
    // printf("vrtcal x >%f\n", cub->ray.vrticlWallHitX);
    // printf("hrzntal --  y >%f\n", cub->ray.horzWallHitY);
    // printf("hrzntal -- x >%f\n", cub->ray.horzWallHitX);
    if (hrzntlDstnc >= vrtclDstnc)
    {
        cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
        cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
        cub->ray.Distance  = vrtclDstnc;
    }
    else
    {
        cub->ray.wallHit_x = cub->ray.horzWallHitX;
        cub->ray.wallHit_y = cub->ray.horzWallHitY;
        cub->ray.Distance  = hrzntlDstnc;
    }
}