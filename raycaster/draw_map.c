/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/06 12:36:40 by yismaili         ###   ########.fr       */
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

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
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

void    ft_bresenham(t_struct *cub)
{
    float   x_step;
    float   y_step;
    float   max;
    char    **data;
    
        data = ft_jump_lines(cub);
        x_step = (cub->cordnt.x_1) - cub->cordnt.x;
        y_step = (cub->cordnt.y_1) - cub->cordnt.y;
        max = ft_max(abs((int)x_step), abs((int)y_step));
        x_step /= max;
        y_step /= max;
    while ((int)(cub->cordnt.x - cub->cordnt.x_1) || (int)(cub->cordnt.y - cub->cordnt.y_1))
    {
        if ( cub->checkColorMap == 1)
        {
                my_mlx_pixel_put(cub, cub->cordnt.x, cub->cordnt.y, 0xffff);  
                cub->checkColorMap = 0;  
        }
        else{
                my_mlx_pixel_put(cub, cub->cordnt.x, cub->cordnt.y, 0x00FF0000); 
         }
		cub->cordnt.x = cub->cordnt.x + x_step;
		cub->cordnt.y = cub->cordnt.y + y_step;
    }
}

void    ft_coordinate(int x, int y, t_struct *cub, int check)
{
    if (check == 0)
    {
        cub->cordnt.x = x;
        cub->cordnt.x_1 = x + 1;
        cub->cordnt.y = y;
        cub->cordnt.y_1 = y;
    }
    if (check == 1)
    {
        cub->cordnt.x = x;
        cub->cordnt.x_1 = x;
        cub->cordnt.y = y;
        cub->cordnt.y_1 = y + 1;
    }
    ft_bresenham(cub);
}

void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    int height;
    char    **data;
    int     len;
   

    y = 0;
    len = 0;
    cub->checkColorMap = 0;
    data = ft_jump_lines(cub);
    height = ft_count_height(data);
    while (data[y])
    {
        x = 0;
        //len = ft_strlen(data[y]);
        while (data[y][x])
        {
            if (data[y][x] == '1')
            {
                 cub->checkColorMap = 1;
            }
            // if (x < len - 1)
            //     ft_coordinate(x, y, cub, 0);
            if (y < height - 1)
                ft_coordinate(x, y, cub, 1);
           x++;
        }
       y++;
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}