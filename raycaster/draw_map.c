/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/13 13:31:39 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
}
void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    int height;
    char    **data;

    y = 0;
    data = ft_jump_lines(cub);
    height = ft_count_height(data);
    while (y < height)
    {
        x = 0;
        while (x < cub->width)
        {
            if (x < cub->width - 1)
                ft_coordinate(x, y, cub, 0);
            if (y < height - 1)
                ft_coordinate(x, y, cub, 1);
            x++;
        }
        y++;
    }
    
}