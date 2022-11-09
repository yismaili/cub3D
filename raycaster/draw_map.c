/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/09 21:37:36 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_struct *ptr, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		dst = ptr->addr + (y * ptr->line_length + x
				* (ptr->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int ft_count_height(char **data)
{
    int len;
    int i;
    int j;

    i = 0;
    len = 0;
    while (data[i])
    {
        j = 0;
        while (data[i][j])
        {
          if (j == 0)
            len++;
          j++;  
        }
      i++;  
    }
   return (len); 
}

void    draw_cub(t_struct *ptr, int x, int y, int color)
{
    int start_x;
    int start_y;
    int     i;
    int     j;
    char    **data;
    
    data = ft_jump_lines(ptr);
    int  height = ft_count_height(data);
    int scaleHeight = W_HEIGHT/ height ;
    int scaleWidth = W_WIDTH/ ptr->width;
    start_x = x * scaleWidth;
    start_y = y * scaleHeight;
    i = start_y;
    j = start_x;
    if (color == 0xfffff)
    {
       while (i < start_y + scaleHeight)
        {
             my_mlx_pixel_put(ptr, j, i,color);
            i++;
        }
    }
    else {
        
        while (i < start_y + scaleHeight)
        {
            j =  start_x;
            while (j < start_x + scaleWidth)
            {
                my_mlx_pixel_put(ptr, j, i,color);
                j++;
            }
            i++;
        }
    }
}

void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    char    **data;
    int     len;

    y = 0;
    len = 0;
    data = ft_jump_lines(cub);
    while (data[y])
    {
        x = 0;
        while (data[y][x])
        {
            if (data[y][x] == '1')
                draw_cub(cub, x, y, 0xFF00000);
            else if (y == cub->player.position_y && x == cub->player.position_x){
                 draw_player(cub, x, y, 0xfffff);
            }
            else
                draw_cub(cub, x, y, 0);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 1, 1);
}

void player_position(t_struct *cub){
    int i = 0;
    int j = 0;
   char** data = ft_jump_lines(cub);
   while (data[i])
   {
    j = 0;
    while(data[i][j]){
        if (data[i][j] == 'E'|| data[i][j] == 'N' || data[i][j] == 'S' || data[i][j] == 'W'){
        cub->player.position_x = j;
        cub->player.position_y = i;
        return ;
        }
        j++;
    }
    i++;
   } 
}

int	player_move(int key, t_struct *p)
{
    printf("%d\n",key);
	if (key == 1)
		p->player.position_y += 1;
	if (key == 13)
		p->player.position_y -= 1;
	if (key == 2)
		p->player.position_x += 1;
	if (key == 0)
		p->player.position_x -= 1;
    if (key == 124)
		p->player.rottAngle += 30;
	if (key == 123)
		p->player.rottAngle -= 30;
    mlx_destroy_image(p->mlx_ptr, p->img);
    p->img = mlx_new_image(p->mlx_ptr, W_WIDTH, W_HEIGHT);
    ft_draw_map(p);
    return (0);
}

void directionOfPlayer(t_struct *cub){
    
    char** data = ft_jump_lines(cub);
    if (data[cub->player.position_y][cub->player.position_x] == 'N'){
        cub->player.rottAngle = M_PI / 2;
     }
    if (data[cub->player.position_y][cub->player.position_x] == 'S'){
        cub->player.rottAngle = M_PI *(3/2);
     }
    if (data[cub->player.position_y][cub->player.position_x] == 'W'){
        cub->player.rottAngle = M_PI;
     }
    if (data[cub->player.position_y][cub->player.position_x] == 'E'){
        cub->player.rottAngle = 0;
     }
}

void draw_player(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;

	x_1 = x + cos(cub->player.rottAngle) * 30;
    y_1 = y + sin(cub->player.rottAngle) * 30;
    ddaForLine(cub, x,y,x_1,y_1,color);  
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
    // calculate dstncx & dstncy
    int dstncx = x_1 - x_0;
    int dstncy = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstncx) > abs(dstncy))
        steps = abs(dstncx);
    else
        steps = abs(dstncy);
    // calculate increment in x & y for each steps
    float Xinc = dstncx / (float)steps;
    float Yinc = dstncy / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += Xinc; // increment in x at each step
       y += Yinc; // increment in y at each step
       i++;
    }
}
 