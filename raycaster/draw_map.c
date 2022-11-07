/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/07 09:41:43 by yismaili         ###   ########.fr       */
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
    float   p;
    float   p_1;
    
    data = ft_jump_lines(cub);
    p = cub->cordnt.x;
    p_1 = cub->cordnt.x_1;
    cub->cordnt.z = data[(int)cub->cordnt.y][(int)cub->cordnt.x];
    cub->cordnt.z_1 = data[(int)cub->cordnt.y_1][(int)cub->cordnt.x_1];
    cub->cordnt.x = (p - cub->cordnt.y) * cos(cub->cos_x);
    cub->cordnt.y = (p + cub->cordnt.y) * sin(cub->sin_y) ;
    cub->cordnt.x_1 = (p_1 - cub->cordnt.y_1) * cos(cub->cos_x) - cub->cordnt.z;
    cub->cordnt.y_1 = (p_1 + cub->cordnt.y_1) * sin(cub->sin_y) - cub->cordnt.z_1;
    x_step = cub->cordnt.x_1 - cub->cordnt.x;
    y_step = cub->cordnt.y_1 - cub->cordnt.y;
    max = ft_max(abs((int)x_step), abs((int)y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(cub->cordnt.x - cub->cordnt.x_1) || (int)(cub->cordnt.y - cub->cordnt.y_1))
    {
        my_mlx_pixel_put(cub, cub->cordnt.x,  cub->cordnt.y, 0xffff);
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
    float   x_step;
    float   y_step;
    float   max;

    y = 0;
    len = 0;
    data = ft_jump_lines(cub);
    height = ft_count_height(data);
    printf("%d\n",height);
    while (data[y])
    {
        x = 0;
        //len = ft_strlen(data[y]);
         y_step = (y+1) - y;
        while (data[y][x])
        {
            // if (x < len - 1)
            //     ft_coordinate(x, y, cub, 0);
            // if (y < height - 1)
            //     ft_coordinate(x, y, cub, 1);
            x_step = (x+1) - x;
            max = ft_max(abs((int)x_step), abs((int)y_step));
            x_step /= max;
            y_step /= max;
            if (data[y][x] == '1')
            {
                 my_mlx_pixel_put(cub, x, y, 0xffff);    
            }
            else{
                  my_mlx_pixel_put(cub, x, y, 0x00FF0000); 
            }
            x = x + x_step;
        }
        y = y + y_step;
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 100, 100);
}