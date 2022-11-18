/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/18 12:50:41 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* cast all rays */

int castRays(t_struct *cub)
{
    int i;
    i = 0;
    while (i < cub->numOfRays)
    {
       cub->rays[i] = cub->rayAngle;
       cub->rayAngle += cub->fovAngle / cub->numOfRays;
       i++;
    }
    return (0);
}
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
    
    castRays(cub);
    while (cub->rays[i])
    {  
        cub->ray.rayAngle = normalizeAngle(cub->rays[i]);
       
        castAllRays(cub);
    
        ddaForLine(cub, x, y, cub->ray.wallHit_x, cub->ray.wallHit_y,color);
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
//puts("ana");
    map = ft_jump_lines(cub);
    int gred_y = (int)(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->scaleWidth);
    // if((size_t)(gred_x) < ft_strlen(map[gred_y]))
    //     return(1);
    // printf("------------------------------------------------------\n");
    // printf("%s\n",  map[gred_y]);
    // printf("------------------------------------------------------\n");
      if (!map[gred_y])
    {
        return (1);
    }
    if ( map[gred_y][gred_x] == '1' ||  !map[gred_y])
    {
        return (1);
    }
    return (0);
 }

 double normalizeAngle(double angle)
 {
    angle =  fmod(angle,2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    return (angle);
 }
 

double calculDistance(double wallHit_x, double wallHit_y, double x, double y)
{
    return (sqrt(x - wallHit_x) * (x - wallHit_x) + (y - wallHit_y) * (y - wallHit_y));
}
    
void castHrzntalRays(t_struct *cub)
{
    double x_hrzntlIntrsctn;
    double y_hrzntlIntrsctn;
    double y_incrmnt;
    double x_incrmnt;
    double x_nextHrzntal;
    double y_nextHrzntal;

    cub->ray.horzWallHitX = 0;
    cub->ray.horzWallHitY = 0;
    cub->ray.foundHorzWallHit = 0;
    y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (y_hrzntlIntrsctn == cub->ray.rayFacingDown)
        y_hrzntlIntrsctn += cub->ray.rayFacingDown;
    else if (y_hrzntlIntrsctn == cub->scaleHeight)
        y_hrzntlIntrsctn += 0;
    x_hrzntlIntrsctn = cub->player.position_x + (y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
    //    printf("%f\n",x_hrzntlIntrsctn);
    y_incrmnt = cub->scaleHeight;
    if (y_incrmnt == cub->ray.rayFacingUp)
        y_incrmnt *= -1;
    else
        y_incrmnt *= 1;
    x_incrmnt = cub->scaleWidth / (tan(cub->ray.rayAngle));
    if (x_incrmnt == INFINITY)
        x_incrmnt = cub->scaleWidth;
    if (x_incrmnt == cub->ray.rayFacingLeft && x_incrmnt > 0)
        x_incrmnt *= -1;
    else
        x_incrmnt *= 1;
    if (x_incrmnt == cub->ray.rayFacingRight && x_incrmnt < 0)
        x_incrmnt *= -1;
    else
        x_incrmnt *= 1;
    //  printf("%f\n",y_hrzntlIntrsctn);
    x_nextHrzntal = x_hrzntlIntrsctn;
    y_nextHrzntal = y_hrzntlIntrsctn;
    if (cub->ray.rayFacingUp)
        y_nextHrzntal--;
    while (x_nextHrzntal >= 0 && x_nextHrzntal <= W_WIDTH && y_nextHrzntal >= 0 && y_nextHrzntal <= W_HEIGHT )
    {
        if (check_wall(cub, x_nextHrzntal, y_nextHrzntal))
        {
            // printf("hrzntal x ---> %f\n", x_nextHrzntal);
            //  printf("hrzntal x ---> %f\n", y_nextHrzntal);
            cub->ray.foundHorzWallHit = 1;
            cub->ray.horzWallHitX = x_nextHrzntal;
            cub->ray.horzWallHitY = y_nextHrzntal;
            break;
        }
        x_nextHrzntal += x_incrmnt;
        y_nextHrzntal += y_incrmnt;
     }
}

void castVrtcalRays(t_struct *cub)
{
    double y_vrtclIntrsctn;
    double x_vrticallIntrsctn;
    double x_incrmntVrtcl;
    double y_incrmntVrtcl;
    double x_nextVrtcl;
    double y_nextVrtcl;
     
    cub->ray.vrticlWallHitX = 0;
    cub->ray.vrtclWallHitY = 0;
    cub->ray.foundvrtclWallHit = 0;
    x_vrticallIntrsctn =  floor(cub->player.position_x / cub->scaleWidth) * cub->scaleWidth;
    if (x_vrticallIntrsctn == cub->ray.rayFacingDown)
        x_vrticallIntrsctn += cub->ray.rayFacingDown;
    else if (x_vrticallIntrsctn == cub->scaleHeight)
        x_vrticallIntrsctn += 0;
    y_vrtclIntrsctn = cub->player.position_y + (x_vrticallIntrsctn - cub->player.position_x)* tan(cub->ray.rayAngle);
    //  printf("%f\n",y_vrtclIntrsctn);
    x_incrmntVrtcl = cub->scaleWidth;
    if (x_incrmntVrtcl == cub->ray.rayFacingLeft)
        x_incrmntVrtcl *= -1;
    else
        x_incrmntVrtcl *= 1;
    y_incrmntVrtcl = cub->scaleHeight * tan(cub->ray.rayAngle);
    if (y_incrmntVrtcl == INFINITY)
        y_incrmntVrtcl = cub->scaleHeight;
    if (y_incrmntVrtcl == cub->ray.rayFacingUp && y_incrmntVrtcl > 0)
        y_incrmntVrtcl *= -1;
    else 
        y_incrmntVrtcl *= 1;
    if (y_incrmntVrtcl == cub->ray.rayFacingDown && y_incrmntVrtcl < 0)
        y_incrmntVrtcl *= -1;
    else
        y_incrmntVrtcl *= 1;
    //printf("%f\n",x_vrticallIntrsctn);
    x_nextVrtcl = x_vrticallIntrsctn;
    y_nextVrtcl = y_vrtclIntrsctn;
    if (cub->ray.rayFacingUp)
        x_nextVrtcl--;
    while (x_nextVrtcl >= 0 && x_nextVrtcl <= W_WIDTH && y_nextVrtcl >= 0 && y_nextVrtcl <= W_HEIGHT )
    {
        
        if (check_wall(cub, x_nextVrtcl, y_nextVrtcl))
        {
            // printf("vrtcal x ---> %f\n", x_nextVrtcl);
            //  printf("vrtcal y ---> %f\n", y_nextVrtcl);
            cub->ray.foundvrtclWallHit = 1;
            cub->ray.vrticlWallHitX = x_nextVrtcl;
            cub->ray.vrtclWallHitY = y_nextVrtcl;
            break;
        }
        x_nextVrtcl += x_incrmntVrtcl;
        y_nextVrtcl += y_incrmntVrtcl;
     }
}

void castAllRays(t_struct *cub)
{
    double hrzntlDstnc = 0;
    double vrtclDstnc = 0;

    cub->ray.wallHit_x = 0;
    cub->ray.wallHit_y = 0;
    cub->ray.Distance = 0;
    cub->ray.hitVertucal = 0;
    if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI){
            cub->ray.rayFacingDown =  cub->ray.rayAngle;
     }
     else {
        cub->ray.rayFacingUp = cub->ray.rayAngle;
     }
    if (cub->ray.rayAngle < ((1/2)*M_PI) || cub->ray.rayAngle > ((3/2)*M_PI)){
            cub->ray.rayFacingRight =  cub->ray.rayAngle;
     }
     else {
        cub->ray.rayFacingLeft = cub->ray.rayAngle;
     }
     // puts("star");
    castVrtcalRays(cub);
     //puts("end");
    castHrzntalRays(cub);
    //   printf("*****>%f\n",  cub->ray.horzWallHitX);
    //   printf("---->%f\n", cub->player.position_x );
    if (cub->ray.foundHorzWallHit == 1)
        hrzntlDstnc = calculDistance(cub->ray.horzWallHitX/ cub->scaleWidth, cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
    // printf("destace ---> %f\n", hrzntlDstnc);
    if (cub->ray.foundvrtclWallHit == 1)
        vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX/cub->scaleWidth, cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
    if (hrzntlDstnc < vrtclDstnc)
        cub->ray.wallHit_x  = cub->ray.horzWallHitX;
    else
        cub->ray.wallHit_x  =cub->ray.vrticlWallHitX;
    if (hrzntlDstnc < vrtclDstnc)
        cub->ray.wallHit_y  = cub->ray.horzWallHitY;
    else 
        cub->ray.wallHit_y  = cub->ray.vrtclWallHitY;
    if (hrzntlDstnc < vrtclDstnc)
        cub->ray.Distance  = hrzntlDstnc;
    else
        cub->ray.Distance  = vrtclDstnc;
    //   printf("%f\n",  cub->ray.wallHit_x);
    //   printf("%f\n",  cub->ray.wallHit_y);
    //  printf("---> %f\n",cub->ray.Distance);
}