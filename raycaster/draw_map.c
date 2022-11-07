/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/07 13:55:38 by yismaili         ###   ########.fr       */
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
    int scaleHeight = W_HEIGHT/ height;
    int scaleWidth = W_WIDTH/ ptr->width;
    start_x = x * scaleWidth;
    start_y = y * scaleHeight;
    i = start_y;
    j = start_x;
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
            else if (data[y][x] == 'E'|| data[y][x] == 'N' || data[y][x] == 'S' || data[y][x] == 'W'){
                 draw_cub(cub, x, y, 0xfffff);
            }
            else
                draw_cub(cub, x, y, 0);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 1, 1);
}