/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/13 12:49:54 by yismaili         ###   ########.fr       */
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

void    ft_draw_map(t_struct *cub)
{
    int p_x;
    int p_y;
    int height;
    char    **data;

    p_y = 0;
    data = ft_jump_lines(cub);
    height = ft_count_height(data);
    while (p_y < height)
    {
        p_x = 0;
        while (p_x < cub->width)
        {
            if (p_x < cub->width - 1)
                ft_coordinates(p_x, p_y, cub, 0);
            if (p_x < height - 1)
                ft_coordinates(p_x, p_y, cub, 1);
            p_x++;
        }
        p_y++;
    }
    
}